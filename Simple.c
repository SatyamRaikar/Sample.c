#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_SIZE 24
#define MAX_MERGE_DATA_SIZE 50

char sof = '$';

char data[MAX_DATA_SIZE] = {0};
int chksum[4] = {0};
char merge_data[MAX_MERGE_DATA_SIZE] = {0};

typedef enum {
    SET,
    GET,
    OPCODE_COUNT
} OPCODE;

#define DATA_LENGTH 24

bool calculate_checksum() {
    // Placeholder for checksum calculation logic
    // Replace this with your actual checksum calculation algorithm
    for (int i = 0; i < DATA_LENGTH; ++i) {
        chksum[0] += data[i];
    }
    return true;
}

bool merge_data_checksum() {
    calculate_checksum();
    return true;
}

bool create_packet(OPCODE opcode, const char* input_data) {
    if (strlen(input_data) > DATA_LENGTH - 1) {
        fprintf(stderr, "Error: Input data exceeds maximum allowed size\n");
        return false;
    }

    merge_data[0] = sof;
    merge_data[1] = (char)opcode;
    merge_data[2] = (char)((int)opcode >> 8);  // Assuming opcode is 16-bit

    // Copy input data into the data array
    strncpy(data, input_data, DATA_LENGTH);

    merge_data_checksum();
    memcpy(&merge_data[3], chksum, sizeof(chksum));
    merge_data[MAX_MERGE_DATA_SIZE - 1] = '\0';

    // Print the resulting packet for demonstration
    printf("Created Packet: %s\n", merge_data);

    return true;
}

int main() {
    // Example usage
    const char example_data[DATA_LENGTH] = "ExampleData";
    if (!create_packet(SET, example_data)) {
        return 1;  // Indicate error
    }

    return 0;
}
