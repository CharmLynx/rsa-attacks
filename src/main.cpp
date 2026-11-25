#include <chrono>
#include <iostream>
#include <optional>
#include <string>

#include "io.hpp"
#include "hastad.hpp"
#include "padding.hpp"
#include "mitm.hpp"

using namespace std;

const unsigned long E_MITM = 65537;
const unsigned int L_MITM = 20;

double seconds_since(chrono::steady_clock::time_point start) {
    auto end = chrono::steady_clock::now();
    return chrono::duration<double>(end - start).count();
}

void run_hastad(const string& path, unsigned long e) {
    cout << "=== Hastad: " << path << " (e = " << e << ")" << endl;

    BroadcastData data = read_broadcast(path);

    auto start = chrono::steady_clock::now();
    mpz_class m = hastad_attack(data, e);
    double t = seconds_since(start);

    size_t k = (mpz_sizeinbase(data.n[0].get_mpz_t(), 2) + 7) / 8;
    vector<uint8_t> em = to_bytes(m, k);
    vector<uint8_t> payload = strip_pkcs1_v15(em);

    cout << "pairs:   " << data.c.size() << endl;
    cout << "M:       " << to_hex(em) << endl;
    cout << "payload: " << to_hex(payload) << " (" << payload.size() << " bytes)" << endl;
    cout << "time:    " << t << " s" << endl << endl;
}

void run_mitm(const string& path) {
    cout << "=== MitM vs brute force: " << path
         << " (e = " << E_MITM << ", l = " << L_MITM << ")" << endl;

    MitmData data = read_mitm(path);

    auto start = chrono::steady_clock::now();
    optional<MitmResult> r = mitm_attack(data, E_MITM, L_MITM);
    double t_mitm = seconds_since(start);

    if (r) {
        cout << "MitM:        " << r->t << " * " << r->s << " = " << r->t * r->s << endl;
    } else {
        cout << "MitM:        plaintext not determined" << endl;
    }
    cout << "MitM time:   " << t_mitm << " s" << endl;

    start = chrono::steady_clock::now();
    optional<mpz_class> m = brute_force(data, E_MITM, L_MITM);
    double t_bf = seconds_since(start);

    if (m) {
        cout << "brute force: " << *m << endl;
    } else {
        cout << "brute force: not found" << endl;
    }
    cout << "brute time:  " << t_bf << " s" << endl;

    if (r && t_mitm > 0) {
        cout << "speedup:     " << t_bf / t_mitm << "x" << endl;
    }
    cout << endl;
}

int main() {
    try {
        run_hastad("data/se_test.txt", 3);
        run_hastad("data/se.txt", 5);

        run_mitm("data/mitm_test.txt");
        run_mitm("data/mitm.txt");
    } catch (const exception& ex) {
        cerr << "error: " << ex.what() << endl;
        return 1;
    }

    return 0;
}