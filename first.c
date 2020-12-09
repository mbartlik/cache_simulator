#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// structure to represent a line in memory
typedef struct Line {
	int valid;
	long address;
    long tag;
    long set;
    long block;
    int used_time;
    int added_time;
} Line;


// given a character array that is a memory address this will return an equivalent binary int array
int* get_binary_address(char* address) {
	int* binary_address = malloc(48*sizeof(int));
	int place = 48 - 4*strlen(address) + 8;
	int i;
	for(i = 0; i < 48; i = i + 1) {
		binary_address[i] = 0;
	}
	for(i = 2; i < strlen(address); i = i + 1) {
		if(address[i] == '0') {
			binary_address[place] = 0;
			binary_address[place + 1] = 0;
			binary_address[place + 2] = 0;
			binary_address[place + 3] = 0;
		}
		else if(address[i] == '1') {
			binary_address[place] = 0;
			binary_address[place + 1] = 0;
			binary_address[place + 2] = 0;
			binary_address[place + 3] = 1;
		}
		else if(address[i] == '2') {
			binary_address[place] = 0;
			binary_address[place + 1] = 0;
			binary_address[place + 2] = 1;
			binary_address[place + 3] = 0;
		}
		else if(address[i] == '3') {
			binary_address[place] = 0;
			binary_address[place + 1] = 0;
			binary_address[place + 2] = 1;
			binary_address[place + 3] = 1;
		}
		else if(address[i] == '4') {
			binary_address[place] = 0;
			binary_address[place + 1] = 1;
			binary_address[place + 2] = 0;
			binary_address[place + 3] = 0;
		}
		else if(address[i] == '5') {
			binary_address[place] = 0;
			binary_address[place + 1] = 1;
			binary_address[place + 2] = 0;
			binary_address[place + 3] = 1;
		}
		else if(address[i] == '6') {
			binary_address[place] = 0;
			binary_address[place + 1] = 1;
			binary_address[place + 2] = 1;
			binary_address[place + 3] = 0;
		}
		else if(address[i] == '7') {
			binary_address[place] = 0;
			binary_address[place + 1] = 1;
			binary_address[place + 2] = 1;
			binary_address[place + 3] = 1;
		}
		else if(address[i] == '8') {
			binary_address[place] = 1;
			binary_address[place + 1] = 0;
			binary_address[place + 2] = 0;
			binary_address[place + 3] = 0;
		}
		else if(address[i] == '9') {
			binary_address[place] = 1;
			binary_address[place + 1] = 0;
			binary_address[place + 2] = 0;
			binary_address[place + 3] = 1;
		}
		else if(address[i] == 'a') {
			binary_address[place] = 1;
			binary_address[place + 1] = 0;
			binary_address[place + 2] = 1;
			binary_address[place + 3] = 0;
		}
		else if(address[i] == 'b') {
			binary_address[place] = 1;
			binary_address[place + 1] = 0;
			binary_address[place + 2] = 1;
			binary_address[place + 3] = 1;
		}
		else if(address[i] == 'c') {
			binary_address[place] = 1;
			binary_address[place + 1] = 1;
			binary_address[place + 2] = 0;
			binary_address[place + 3] = 0;
		}
		else if(address[i] == 'd') {
			binary_address[place] = 1;
			binary_address[place + 1] = 1;
			binary_address[place + 2] = 0;
			binary_address[place + 3] = 1;
		}
		else if(address[i] == 'e') {
			binary_address[place] = 1;
			binary_address[place + 1] = 1;
			binary_address[place + 2] = 1;
			binary_address[place + 3] = 0;
		}
		else if(address[i] == 'f') {
			binary_address[place] = 1;
			binary_address[place + 1] = 1;
			binary_address[place + 2] = 1;
			binary_address[place + 3] = 1;
		}

		place = place + 4;

	}

	return binary_address;

}

// gets the tag from a binary address
long get_tag(int tag_bits, int* binary_address) {

	int* tag = malloc(tag_bits*sizeof(int));

	int i;
	long place = (long)pow(2.0,tag_bits-1);
	long res = 0;
	for(i = 0; i < tag_bits; i = i + 1) {
		res += binary_address[i]*place;
		place=place/2;
	}
	
	free(tag);
	return res;

}	

// gets the set from a binary address
long get_set(int tag_bits, int set_bits, int* binary_address) {
	
	int* set = malloc(set_bits*sizeof(int));

	int i;
	long place = (long)pow(2.0,set_bits-1);
	long res = 0;
	for(i = tag_bits; i < tag_bits + set_bits; i = i + 1) {
		res += binary_address[i]*place;
		place=place/2;
	}

	free(set);
	return res;

}	

// gets the block from a binary address
long get_block(int tag_bits, int set_bits, int block_bits, int* binary_address) {
	
	int* block = malloc(block_bits*sizeof(int));

	int i;
	long place = (long)pow(2.0,block_bits-1);
	long res = 0;
	for(i = tag_bits + set_bits; i < tag_bits + set_bits + block_bits; i = i + 1) {
		res += binary_address[i]*place;
		place=place/2;
	}

	free(block);
	return res;
}

// checks if two block offsets are in the same chunk of memory
int check_if_same_block(long num1, long num2, int block_size) {

	if((long)(num1/block_size) == (long)(num2/block_size)) {
		return 1;
	}
	return 0;


}

// checks if a number is a power of 2
int check_power_of_2(int num) {
	while(1) {
		if(num % 2 != 0) {
			return 0;
		}
		if(num == 0) {
			return 0;
		}
		if(num == 2) {
			return 1;
		}
		num = num/2;
	}
	return 0;

}

// converts a hexadecimal character array to a decimal number
long convert_hex(char* num) {
	int len = strlen(num); // length of the number
	long place = 1; // multiplies by 16 each time we move up a place
	int i;
	long res = 0;
	long current_digit; // current digit being looked at

	for(i = len - 1; i > 1; i = i - 1) {
		
		if(num[i]>='0' && num[i] <= '9') {
			current_digit = (long)(num[i]) - 48; // subtract 48 for integer value
			res += current_digit*place;
			place = place*16;
			continue;
		}
		else { // must be a character digit
			if(num[i] == 'a') {
				res += 10*place;
			}
			else if(num[i] == 'b') {
				res += 11*place;
			}
			else if(num[i] == 'c') {
				res += 12*place;
			}
			else if(num[i] == 'd') {
				res += 13*place;
			}
			else if(num[i] == 'e') {
				res += 14*place;
			}
			else if(num[i] == 'f') {
				res += 15*place;
			}

			place = place*16;

		}

	}

	return res;
}



int main(int argc, char* argv[])
{

	// read input parameters
	char* cache_size_temp = argv[1];
	char* associativity_temp = argv[2];
	char* replace_policy_temp = argv[3];
	char* block_size_temp = argv[4];

	// check for valid cache and block size
	int cache_size = atoi(cache_size_temp);
	int block_size = atoi(block_size_temp);

	if(check_power_of_2(cache_size) == 0 || check_power_of_2(block_size) == 0) {
		printf("error\n");
		return 0;
	}

	// check for valid associativity type and store associativity value
	// 0-direct
	// 1-assoc
	// 2-assoc:n
	int associativity;
	int associativity_n;
	if(strcmp(associativity_temp,"direct") == 0) {
		associativity = 0;
	}
	else if(strcmp(associativity_temp,"assoc") == 0) {
		associativity = 1;
	}
	else if(associativity_temp[0] == 'a' && associativity_temp[1] == 's' && associativity_temp[2] == 's' && associativity_temp[3] == 'o' && associativity_temp[4] == 'c' && associativity_temp[5] == ':') {
		associativity = 2;
		associativity_n = atoi(&associativity_temp[6]);
		if(check_power_of_2(associativity_n) == 0) {
			printf("error\n");
			return 0;
		}
	}
	else {
		printf("error\n");
		return 0;
	}

	// check for valid replacement policy
	// 0-lru
	// 1-fifo
	int replace_policy;
	if(strcmp(replace_policy_temp,"lru") == 0) {
		replace_policy = 0;
	}
	else if(strcmp(replace_policy_temp,"fifo") == 0) {
		replace_policy = 1;
	}
	else {
		printf("error\n");
		return 0;
	}


	// find number of block bits
	int block_size_copy = block_size;
	int block_bits = 0;
	while(block_size_copy > 1) {
		block_size_copy = block_size_copy/2;
		block_bits += 1;
	}

	// find number of set bits
	int num_lines = cache_size/block_size;
	int num_sets;
	int lines_per_set;
	int set_bits = 0;
	if(associativity == 0) {
		num_sets = num_lines;
		lines_per_set = 1;
	}
	else if(associativity == 1) {
		num_sets = 1;
		lines_per_set = num_lines;
	}
	else {
		num_sets = num_lines/associativity_n;
		lines_per_set = associativity_n;
	}
	int num_sets_temp = num_sets;
	while(num_sets_temp > 1) {
		num_sets_temp = num_sets_temp/2;
		set_bits += 1;
	}

	// find number of tag bits
	int tag_bits = 48 - block_bits - set_bits;

	// construct cache
	Line cache[num_sets][lines_per_set];
	int i;
	int j;
	for(i = 0; i < num_sets; i = i + 1) {
		for(j = 0; j < lines_per_set; j = j + 1) {
			cache[i][j].valid = 0;
		}
	}

	// read file
    char* filename = argv[5];
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        printf("Error\n");
        return 0;
    }

    // Variables to store input values
    char* pc = malloc(30*sizeof(char));
    char read_or_write;
    char* address = malloc(30*sizeof(char));

    // these store parts of the memory address
    int* binary_address;
    long tag;
    long set;
    long block;

    int time = 0; // keeps track of time, for checking to see when parts of memory are accessed
    int data_placed = 0; // boolean for checking if a hit was made or if a spot for data was found
    int evict_index = 0; // for keeping track of which line should be evicted

    // variables to keep track of metrics for final output
    int memory_reads = 0;
    int memory_writes = 0;
    int cache_hits = 0;
    int cache_misses = 0;


    while(1) {

    	fscanf(file, "%s %c %s \n", pc, &read_or_write, address);

    	// check for end of file
    	if(pc[0] == '#') {
    		break;
    	}

    	// gets binary address and tag, set, block
    	binary_address = get_binary_address(address);
		tag = get_tag(tag_bits, binary_address);
		set = get_set(tag_bits, set_bits, binary_address);
		block = get_block(tag_bits, set_bits, block_bits, binary_address);

		// perform read
    	if(read_or_write == 'R') {

    		// direct associativity
    		if(associativity == 0) {
    			if(cache[set][0].valid == 0) { // line is empty, fill it
    				cache[set][0].valid = 1;
    				cache[set][0].address = convert_hex(address);
    				cache[set][0].tag = tag;
    				cache[set][0].set = set;
    				cache[set][0].block = block;
    				cache_misses += 1;
    				memory_reads += 1;
    			}
    			else {
    				if(cache[set][0].tag == tag) { // if the tag matches
    					if(check_if_same_block(convert_hex(address), cache[set][0].address, block_size) == 1) { 
    						cache_hits += 1;
    					}
    					else { // block offset is not in the same block, update the line
    						cache[set][0].address = convert_hex(address);
		    				cache[set][0].tag = tag;
		    				cache[set][0].set = set;
		    				cache[set][0].block = block;
		    				cache_misses += 1;
		    				memory_reads += 1;
    					}
    				}
    				else { // tag does not match, update the line
    						cache[set][0].address = convert_hex(address);
		    				cache[set][0].tag = tag;
		    				cache[set][0].set = set;
		    				cache[set][0].block = block;
		    				cache_misses += 1;
		    				memory_reads += 1;
    				}
    			}
    		}

    		// fully associative
    		else if(associativity == 1) {
    			for(i = 0; i < num_lines; i = i + 1) { // iterate through every line checking for tag match
    				if(cache[0][i].tag == tag) { // tag match
    					data_placed = 1;
    					if(check_if_same_block(convert_hex(address), cache[0][i].address, block_size) == 1) { 
    						cache_hits += 1;
    						cache[0][i].used_time = time;
    					}
    					else { // block offset not in same block, update line
    						cache[0][i].address = convert_hex(address);
		    				cache[0][i].tag = tag;
		    				cache[0][i].set = set;
		    				cache[0][i].block = block;
		    				cache[0][i].used_time = time;
	    					cache[0][i].added_time = time;
		    				cache_misses += 1;
		    				memory_reads += 1;
    					}
    				}

    				if(data_placed == 1) { // stop iterating if we got a hit or updated the line
    					break;
    				}

    				if(replace_policy == 0) { // lru
    					if(cache[0][i].used_time < cache[0][evict_index].used_time) {
    						evict_index = i;
    					}
    				}
    				else { // fifo
    					if(cache[0][i].added_time < cache[0][evict_index].added_time) {
    						evict_index = i;
    					}
    				}
    			}

    			for(i = 0; i < num_lines; i = i + 1) { // iterate through all lines looking for invalid line
	    			if(cache[0][i].valid == 0) { // line is empty, fill it
						cache[0][i].valid = 1;
	    				cache[0][i].address = convert_hex(address);
	    				cache[0][i].tag = tag;
	    				cache[0][i].block = block;
	    				cache[0][i].used_time = time;
	    				cache[0][i].added_time = time;
	    				cache_misses += 1;
	    				memory_reads += 1;
	    				data_placed = 1; 
	    			}
	    			if(data_placed == 1) {
	    				break;
	    			}
	    		}

    			if(data_placed == 0) { // must evict something
    				cache[0][evict_index].address = convert_hex(address);
    				cache[0][evict_index].tag = tag;
    				cache[0][evict_index].set = set;
    				cache[0][evict_index].block = block;
    				cache[0][evict_index].used_time = time;
					cache[0][evict_index].added_time = time;
    				cache_misses += 1;
    				memory_reads += 1;
    			}

    		}

    		else { // n-way associative
    			for(i = 0; i < associativity_n; i = i + 1) { // iterate through the set for matching tag
    				if(cache[set][i].tag == tag) { // tag match
    					data_placed = 1;
    					if(check_if_same_block(convert_hex(address), cache[set][i].address, block_size) == 1) { 
    						cache_hits += 1;
    						cache[set][i].used_time = time;
    					}
    					else { // block offset is not in same block, update line
    						cache[set][i].address = convert_hex(address);
		    				cache[set][i].tag = tag;
		    				cache[set][i].set = set;
		    				cache[set][i].block = block;
		    				cache[set][i].used_time = time;
	    					cache[set][i].added_time = time;
		    				cache_misses += 1;
		    				memory_reads += 1;
    					}
    				}
    				if(data_placed == 1) { // stop iterating if data placed
    					break;
    				}

    				if(replace_policy == 0) { // lru
    					if(cache[set][i].used_time < cache[set][evict_index].used_time) {
    						evict_index = i;
    					}
    				}
    				else { // fifo
    					if(cache[set][i].added_time < cache[set][evict_index].added_time) {
    						evict_index = i;
    					}
    				}
    			}
    			for(i = 0; i < associativity_n; i = i + 1) { // look for invalid line
    				if(cache[set][i].valid == 0) {
    					cache[set][i].valid = 1;
	    				cache[set][i].address = convert_hex(address);
	    				cache[set][i].tag = tag;
	    				cache[set][i].block = block;
	    				cache[set][i].used_time = time;
	    				cache[set][i].added_time = time;
	    				cache_misses += 1;
	    				memory_reads += 1;
	    				data_placed = 1; 
    				}
    				if(data_placed == 1) {
    					break;
    				}
    			}
    			if(data_placed == 0) { // must evict something
    				cache[set][evict_index].address = convert_hex(address);
    				cache[set][evict_index].tag = tag;
    				cache[set][evict_index].set = set;
    				cache[set][evict_index].block = block;
    				cache[set][evict_index].used_time = time;
					cache[set][evict_index].added_time = time;
    				cache_misses += 1;
    				memory_reads += 1;
    			}

    		}
    	}

    	else { // Must be a memory write

    		memory_writes += 1;

    		// direct associativity
    		if(associativity == 0) {
    			if(cache[set][0].valid == 0) { // line is empty, fill it
    				cache[set][0].valid = 1;
    				cache[set][0].address = convert_hex(address);
    				cache[set][0].tag = tag;
    				cache[set][0].set = set;
    				cache[set][0].block = block;
    				memory_reads += 1;
    				cache_misses += 1;
    			}
    			else {
    				if(cache[set][0].tag == tag) { // tag match
    					if(check_if_same_block(convert_hex(address), cache[set][0].address, block_size) == 1) { 
    						cache_hits += 1;
    					}
    					else { // bad block offset, update line
    						cache[set][0].address = convert_hex(address);
		    				cache[set][0].tag = tag;
		    				cache[set][0].set = set;
		    				cache[set][0].block = block;
		    				cache_misses += 1;
		    				memory_reads += 1;
    					}
    				}
    				else {// tag does not match, update line
						cache[set][0].address = convert_hex(address);
	    				cache[set][0].tag = tag;
	    				cache[set][0].set = set;
	    				cache[set][0].block = block;
	    				cache_misses += 1;
	    				memory_reads += 1;
    				}
    			}
    		}

    		// fully associative
    		else if(associativity == 1) {
    			for(i = 0; i < num_lines; i = i + 1) { // iterate through lines looking for matching tag
    				if(cache[0][i].tag == tag) { // tag match
    					data_placed = 1;
    					if(check_if_same_block(convert_hex(address), cache[0][i].address, block_size) == 1) { 
    						cache_hits += 1;
    						cache[0][i].used_time = time;
    					}
    					else { // block offset no good, update line
    						cache[0][i].address = convert_hex(address);
		    				cache[0][i].tag = tag;
		    				cache[0][i].set = set;
		    				cache[0][i].block = block;
		    				cache[0][i].used_time = time;
	    					cache[0][i].added_time = time;
		    				cache_misses += 1;
		    				memory_reads += 1;
    					}
    				}

    				if(data_placed == 1) { // stop iterating if data placed
    					break;
    				}

    				if(replace_policy == 0) { // lru
    					if(cache[0][i].used_time < cache[0][evict_index].used_time) {
    						evict_index = i;
    					}
    				}
    				else { // fifo
    					if(cache[0][i].added_time < cache[0][evict_index].added_time) {
    						evict_index = i;
    					}
    				}
    			}

    			for(i = 0; i < num_lines; i = i + 1) { // look for an invalid line to fill
	    			if(cache[0][i].valid == 0) { // line is empty, fill it
						cache[0][i].valid = 1;
	    				cache[0][i].address = convert_hex(address);
	    				cache[0][i].tag = tag;
	    				cache[0][i].block = block;
	    				cache[0][i].used_time = time;
	    				cache[0][i].added_time = time;
	    				cache_misses += 1;
	    				memory_reads += 1;
	    				data_placed = 1; 
	    			}
	    			if(data_placed == 1) {
	    				break;
	    			} 
	    		}

    			if(data_placed == 0) { // must evict something
    				cache[0][evict_index].address = convert_hex(address);
    				cache[0][evict_index].tag = tag;
    				cache[0][evict_index].set = set;
    				cache[0][evict_index].block = block;
    				cache[0][evict_index].used_time = time;
					cache[0][evict_index].added_time = time;
    				cache_misses += 1;
    				memory_reads += 1;
    			}

    		}

    		// n-way associative
    		else { 
    			for(i = 0; i < associativity_n; i = i + 1) { // iterate through set looking for matching tag
    				if(cache[set][i].tag == tag) {
    					data_placed = 1;
    					if(check_if_same_block(convert_hex(address), cache[set][i].address, block_size) == 1) { 
    						cache_hits += 1;
    						cache[set][i].used_time = time;
    					}
    					else { // bad block offset, update line
    						cache[set][i].address = convert_hex(address);
		    				cache[set][i].tag = tag;
		    				cache[set][i].set = set;
		    				cache[set][i].block = block;
		    				cache[set][i].used_time = time;
	    					cache[set][i].added_time = time;
		    				cache_misses += 1;
		    				memory_reads += 1;
    					}
    				}
    				if(data_placed == 1) { // data placed, break loop
    					break;
    				}

    				if(replace_policy == 0) { // lru
    					if(cache[set][i].used_time < cache[set][evict_index].used_time) {
    						evict_index = i;
    					}
    				}
    				else { // fifo
    					if(cache[set][i].added_time < cache[set][evict_index].added_time) {
    						evict_index = i;
    					}
    				}
    			}
    			for(i = 0; i < associativity_n; i = i + 1) { // look for invalid line to fill
    				if(cache[set][i].valid == 0) {
    					cache[set][i].valid = 1;
	    				cache[set][i].address = convert_hex(address);
	    				cache[set][i].tag = tag;
	    				cache[set][i].block = block;
	    				cache[set][i].used_time = time;
	    				cache[set][i].added_time = time;
	    				cache_misses += 1;
	    				memory_reads += 1;
	    				data_placed = 1; 
    				}
    				if(data_placed == 1) {
    					break;
    				}
    			}
    			if(data_placed == 0) { // must evict something
    				cache[set][evict_index].address = convert_hex(address);
    				cache[set][evict_index].tag = tag;
    				cache[set][evict_index].set = set;
    				cache[set][evict_index].block = block;
    				cache[set][evict_index].used_time = time;
					cache[set][evict_index].added_time = time;
    				cache_misses += 1;
    				memory_reads += 1;
    			}

    		}
    	}

    	time += 1;
    	free(binary_address);
    	data_placed = 0;
    	evict_index = 0;

    }


    // display results
    printf("Memory reads: %d\n", memory_reads);
    printf("Memory writes: %d\n", memory_writes);
    printf("Cache hits: %d\n", cache_hits);
    printf("Cache misses: %d\n", cache_misses);

    free(address);
    free(pc);


}

// scp -r /Users/maxbartlik/desktop/coding/comp_arch/hw6/hw6-autograder/hw6/first.c mjb556@ilab.cs.rutgers.edu:/ilab/users/mjb556/cs211/hw6/hw6-autograder/hw6

