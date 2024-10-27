#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>


// C++ code
//
const byte Baris = 4; //Menyatakan bahwa terdapat 4 baris pada keypad
const byte Kolom = 4; //Menyatakan bahwa terdapat 4 kolom pada keypad
char password[Baris][Kolom] = { // Membuat array 2D bernama password
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte PinKolom[Kolom] = {9, 8, 7, 6}; // Menghubungkan pin kolom dengan arduino
byte PinBaris[Baris] = {5, 4, 3, 2}; // Menghubungkan pin baris dengan arduino

Keypad tombol = Keypad(makeKeymap(password), PinKolom, PinBaris, Kolom, Baris); // Mendekrasikan kelas keypad bernama tombol
LiquidCrystal layar(12, 11, 13, A0, A1, A2); // Mendeklarasikan kelas Liquidclass bernama layar
Servo gembok; // Mendeklarasikan kelas servo bernama gembok

String pass = "2447"; // Setel password untuk keypad
String input = ""; // Setel input dari user


void setup(){
  layar.begin(16,2); // Banyak kolom dan baris pada lcd
  delay(1000);
  gembok.attach(10); // Attach servo di pin 10
  gembok.write(0); // Posisi awal servo
  layar.print("Enter Code: "); // Output berupa Enter Code: pada display
}

void loop(){
  char kunci = tombol.getKey(); // Mengecek apakah tombol sudah ditekan dan jika sudah akan menyimpan karakter ke variabel kunci
  
  if (kunci) {
    input += kunci; // Memassukan input dari keypad ke string input
    layar.setCursor(0,1); // Menyetel apa yang di input di layar
    layar.print(input); // Memperlihatkan input pada layar
    
    if (input.length() == 4){ //Jika input memiliki panjang 4
      delay(500);
      if (input == pass) { // Jika input sama dengan pass
        layar.clear();
        layar.print("ACCESS GRANTED"); // Memperlihatkan ouput ACCESS GRANTED di layar
        gembok.write(90); // Servo berputar 90 derajat
        delay(5000);
        gembok.write(0);
        delay(2000);
        layar.clear();
        layar.print("Enter Code: "); // Mengulang kembali ke posisi awal
      } else { // Jika input berbeda dengan pass atau lebih/kurang dari 4
        layar.clear();
        layar.print("ACCESS DENIED"); //Memperlihatkan output ACCESS DENIED di layar
        delay(2000); 
        layar.clear();
        layar.print("Enter Code: "); // Mengulang kembali ke posisi awal
      }
      input = ""; // Menyetel input menjadi kosong
      gembok.write(0); // Menyetel servo ke posisi semula
    }
  }
}