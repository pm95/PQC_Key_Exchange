echo "Compiling Alice ... "

gcc Alice.c -lm -static ./PQCrypto-SIDH/lib434/libsidh.a -o alice && ./alice
