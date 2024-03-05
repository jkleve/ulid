#include "ulid/ulid.h"

#include <cassert>

namespace ulid {

// namespace details {
// ulid generate(std::function<uint8_t()>& gen) {
//     gen();
//     return ulid{};
// }
// }  // namespace details

char constexpr char_map[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
    'D', 'E', 'F', 'G', 'H', 'J', 'K', 'M', 'N', 'P', 'Q', 'R', 'S',
    'T', 'V', 'W', 'X', 'Y', 'Z'
};

void to_string(ulid const& ulid, char dst[26]) {
	// 10 byte timestamp
	dst[0] = char_map[(static_cast<uint8_t>(ulid >> 120) & 224) >> 5];
	dst[1] = char_map[static_cast<uint8_t>(ulid >> 120) & 31];
	dst[2] = char_map[(static_cast<uint8_t>(ulid >> 112) & 248) >> 3];
	dst[3] = char_map[((static_cast<uint8_t>(ulid >> 112) & 7) << 2) | ((static_cast<uint8_t>(ulid >> 104) & 192) >> 6)];
	dst[4] = char_map[(static_cast<uint8_t>(ulid >> 104) & 62) >> 1];
	dst[5] = char_map[((static_cast<uint8_t>(ulid >> 104) & 1) << 4) | ((static_cast<uint8_t>(ulid >> 96) & 240) >> 4)];
	dst[6] = char_map[((static_cast<uint8_t>(ulid >> 96) & 15) << 1) | ((static_cast<uint8_t>(ulid >> 88) & 128) >> 7)];
	dst[7] = char_map[(static_cast<uint8_t>(ulid >> 88) & 124) >> 2];
	dst[8] = char_map[((static_cast<uint8_t>(ulid >> 88) & 3) << 3) | ((static_cast<uint8_t>(ulid >> 80) & 224) >> 5)];
	dst[9] = char_map[static_cast<uint8_t>(ulid >> 80) & 31];

	// 16 bytes of entropy
	dst[10] = char_map[(static_cast<uint8_t>(ulid >> 72) & 248) >> 3];
	dst[11] = char_map[((static_cast<uint8_t>(ulid >> 72) & 7) << 2) | ((static_cast<uint8_t>(ulid >> 64) & 192) >> 6)];
	dst[12] = char_map[(static_cast<uint8_t>(ulid >> 64) & 62) >> 1];
	dst[13] = char_map[((static_cast<uint8_t>(ulid >> 64) & 1) << 4) | ((static_cast<uint8_t>(ulid >> 56) & 240) >> 4)];
	dst[14] = char_map[((static_cast<uint8_t>(ulid >> 56) & 15) << 1) | ((static_cast<uint8_t>(ulid >> 48) & 128) >> 7)];
	dst[15] = char_map[(static_cast<uint8_t>(ulid >> 48) & 124) >> 2];
	dst[16] = char_map[((static_cast<uint8_t>(ulid >> 48) & 3) << 3) | ((static_cast<uint8_t>(ulid >> 40) & 224) >> 5)];
	dst[17] = char_map[static_cast<uint8_t>(ulid >> 40) & 31];
	dst[18] = char_map[(static_cast<uint8_t>(ulid >> 32) & 248) >> 3];
	dst[19] = char_map[((static_cast<uint8_t>(ulid >> 32) & 7) << 2) | ((static_cast<uint8_t>(ulid >> 24) & 192) >> 6)];
	dst[20] = char_map[(static_cast<uint8_t>(ulid >> 24) & 62) >> 1];
	dst[21] = char_map[((static_cast<uint8_t>(ulid >> 24) & 1) << 4) | ((static_cast<uint8_t>(ulid >> 16) & 240) >> 4)];
	dst[22] = char_map[((static_cast<uint8_t>(ulid >> 16) & 15) << 1) | ((static_cast<uint8_t>(ulid >> 8) & 128) >> 7)];
	dst[23] = char_map[(static_cast<uint8_t>(ulid >> 8) & 124) >> 2];
	dst[24] = char_map[((static_cast<uint8_t>(ulid >> 8) & 3) << 3) | (((static_cast<uint8_t>(ulid)) & 224) >> 5)];
	dst[25] = char_map[(static_cast<uint8_t>(ulid)) & 31];
}

std::string to_string(ulid const& id) {
    char data[27];
    data[26] = '\0';
    to_string(id, data);
    return std::string(data);
}

static const uint8_t dec[256] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	/* 0     1     2     3     4     5     6     7  */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	/* 8     9                                      */
	0x08, 0x09, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

	/*    10(A) 11(B) 12(C) 13(D) 14(E) 15(F) 16(G) */
	0xFF, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
	/*17(H)     18(J) 19(K)       20(M) 21(N)       */
	0x11, 0xFF, 0x12, 0x13, 0xFF, 0x14, 0x15, 0xFF,
	/*22(P)23(Q)24(R) 25(S) 26(T)       27(V) 28(W) */
	0x16, 0x17, 0x18, 0x19, 0x1A, 0xFF, 0x1B, 0x1C,
	/*29(X)30(Y)31(Z)                               */
	0x1D, 0x1E, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

ulid from_string(std::string const& str) {
    assert(str.length() == 26);
    ulid id;
    from_string(str.c_str(), id);
    return id;
}

void from_string(char const str[26], ulid& id) {
	// timestamp
	id = (dec[int(str[0])] << 5) | dec[int(str[1])];

	id <<= 8;
	id |= (dec[int(str[2])] << 3) | (dec[int(str[3])] >> 2);

	id <<= 8;
	id |= (dec[int(str[3])] << 6) | (dec[int(str[4])] << 1) | (dec[int(str[5])] >> 4);

	id <<= 8;
	id |= (dec[int(str[5])] << 4) | (dec[int(str[6])] >> 1);

	id <<= 8;
	id |= (dec[int(str[6])] << 7) | (dec[int(str[7])] << 2) | (dec[int(str[8])] >> 3);

	id <<= 8;
	id |= (dec[int(str[8])] << 5) | dec[int(str[9])];

	// entropy
	id <<= 8;
	id |= (dec[int(str[10])] << 3) | (dec[int(str[11])] >> 2);

	id <<= 8;
	id |= (dec[int(str[11])] << 6) | (dec[int(str[12])] << 1) | (dec[int(str[13])] >> 4);

	id <<= 8;
	id |= (dec[int(str[13])] << 4) | (dec[int(str[14])] >> 1);

	id <<= 8;
	id |= (dec[int(str[14])] << 7) | (dec[int(str[15])] << 2) | (dec[int(str[16])] >> 3);

	id <<= 8;
	id |= (dec[int(str[16])] << 5) | dec[int(str[17])];

	id <<= 8;
	id |= (dec[int(str[18])] << 3) | (dec[int(str[19])] >> 2);

	id <<= 8;
	id |= (dec[int(str[19])] << 6) | (dec[int(str[20])] << 1) | (dec[int(str[21])] >> 4);

	id <<= 8;
	id |= (dec[int(str[21])] << 4) | (dec[int(str[22])] >> 1);

	id <<= 8;
	id |= (dec[int(str[22])] << 7) | (dec[int(str[23])] << 2) | (dec[int(str[24])] >> 3);

	id <<= 8;
	id |= (dec[int(str[24])] << 5) | dec[int(str[25])];}

}  // namespace ulid