# Endian-ness
- Example: 
    ```c
    int x = 0x12345678; // 32 bit integer
    ```

    Byte groups:
    ```c
    0x12: MSByte
    0x34
    0x56
    0x78: LSByte
    ```

    Let the address of `x`: 
    ```c
    &x: 0x7ffc56e6b8bc // this is the starting address of the variable. 
    ```

    We know that, `sizeof(int)` = 4 Bytes
    Distribution: 
    ```c
    0x7ffc56e6b8bc: // 1st byte | base address | lowest address
    0x7ffc56e6b8bd: // 2nd byte
    0x7ffc56e6b8be: // 3rd byte
    0x7ffc56e6b8bf: // 4th byte
    ```
## Big Endian
- A byte - ordering technique, in which the Most Significant Byte of a multi - byte data type is stored in the lowest memory address. 
- The most significant Byte goes into the Lowest address. 
    ```c
    0x7ffc56e6b8bc: 0x12
    0x7ffc56e6b8bd: 0x34
    0x7ffc56e6b8be: 0x56
    0x7ffc56e6b8bf: 0x78
    ```
## Little Endian
- A byte - ordering technique, in which the Least Significant Byte of a multi - byte data type is stored in the lowest memory address. 
- The least significant Byte goes into the Lowest address. 
    ```c
    0x7ffc56e6b8bc: 0x78
    0x7ffc56e6b8bd: 0x56
    0x7ffc56e6b8be: 0x34
    0x7ffc56e6b8bf: 0x12
    ```
