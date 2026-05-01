# Endian-ness
- Consider the given scenario: 
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
- CPU rearranges the content before printing. 
    ```c
    0x7ffc56e6b8bc: 0x78
    0x7ffc56e6b8bd: 0x56
    0x7ffc56e6b8be: 0x34
    0x7ffc56e6b8bf: 0x12
    ```
_____________
## Endianness and Programming

- Consider the commands:
    ```c
    char* c = (char*)&x;
    short* s = (short*)&x;
    int* i = (int*)&x;
    ```

|         Command           |   Big Endian  |   Little Endian   |
| ---                       | ---           | ---               |
|   printf("%x", (int)*c);  |      0x12     |       0x78        |
|   printf("%x", (int)*s);  |      0x1234   |       0x5678      |
|   printf("%x", (int)*i);  |    0x12345678 |     0x12345678    |

- All the variables are made to point to the same memory location; that is `&x`. 
- The difference is that, 
    - `char` pointer reads exactly one byte (its base adress itself). 
    - `short` pointer reads two bytes (base address + next byte). 
    - `int` pointer reads 4 bytes (base address + next 3 bytes). 
- In **Big Endian System**, when reading multiple bytes, the order stored and the order printed are the same, CPU does not do any reordering here. 
- In **Little Endian System**, when reading multiple bytes, the order printed is the **REVERSE** of the order in which the contents are stored. 
    ```c
    printf("%x", (int)*s); 
    ```

    ```
    s: 0x7ffc56e6b8bc
    Since s is short datatype, we will take the next address also; 
    that is 
    0x7ffc56e6b8bd. 

    Big Endian (take the content, print as is)
    0x7ffc56e6b8bc: 0x12
    0x7ffc56e6b8bd: 0x34

    Output: 0x1234

    Little Endian (take the content, and then reverse the order)
    0x7ffc56e6b8bc: 0x78
    0x7ffc56e6b8bd: 0x56

    Output: 0x5678 (reversed)
    ```
