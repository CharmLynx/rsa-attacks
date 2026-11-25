#include "padding.hpp"

#include <stdexcept>

using namespace std;

vector<uint8_t> to_bytes(const mpz_class& x, size_t len) {
    if (x < 0) {
        throw invalid_argument("to_bytes: negative number");
    }

    size_t need = (mpz_sizeinbase(x.get_mpz_t(), 2) + 7) / 8;
    if (need > len) {
        throw invalid_argument("to_bytes: number does not fit in " +
                               to_string(len) + " bytes");
    }

    vector<uint8_t> bytes(len, 0);
    size_t written = 0;
    mpz_export(bytes.data() + (len - need), &written,
               1, 1, 1, 0, x.get_mpz_t());

    return bytes;
}

vector<uint8_t> strip_pkcs1_v15(const vector<uint8_t>& em) {
    if (em.size() < 11) {
        throw invalid_argument("strip_pkcs1_v15: block too short");
    }
    if (em[0] != 0x00) {
        throw invalid_argument("strip_pkcs1_v15: first byte is not 00");
    }
    if (em[1] != 0x01) {
        throw invalid_argument("strip_pkcs1_v15: block type is not 01");
    }

    size_t i = 2;
    while (i < em.size() && em[i] == 0xFF) {
        i++;
    }

    size_t ps_len = i - 2;
    if (ps_len < 8) {
        throw invalid_argument("strip_pkcs1_v15: padding shorter than 8 bytes");
    }
    if (i == em.size() || em[i] != 0x00) {
        throw invalid_argument("strip_pkcs1_v15: no 00 separator after padding");
    }

    return vector<uint8_t>(em.begin() + i + 1, em.end());
}

string to_hex(const vector<uint8_t>& bytes) {
    string hex;

    return hex;
}