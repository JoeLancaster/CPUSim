#ifndef PSW_H
#define PSW_H

union PSW {
	unsigned char s_PSW;
	struct {
		unsigned int Z: 1;
		unsigned int P: 1;
		unsigned int C: 1;
        unsigned int null_bits : 5; //this is required to make the structure up to 8 bits so it fits in the union
	};
};

#endif
