# HandheldEncrypter
This is a final project for both Microcontrollers and Computer Security that uses a Basys MX3 board with a PIC32MX30512H to creata a handheld encrypter and decrypter

Manual:
  
Basys MX3 Encryption Manual
Use:
	This project accepts an 8-bit input using the switches and then, utilizing functions with the buttons, can encrypt and decrypt the input using a randomized key and a secret “n” value.

Functions: 

    Up Button: 
Shows your current key, then randomizes it and shows the new key. It also randomizes the secret “n” value. (IF THIS IS PUSHED BETWEEN ENCRYPTION AND DECRYPTION, THE PLAIN-TEXT WILL NOT BE RECOVERABLE)

	Left/Right Button:
Changes the current mode. If the RGB flashes red, the current mode is encryption. If it flashes blue, the current mode is decryption.

	Center Button: 
Carries out the current active mode. It will flash the RGB with the mode it is performing, then display the output using the LEDs.

	Down Button:
Flashes the RGB with the current mode, displays the current key, and sets the input for the function with the switches that are currently activated.

To Use: 
Turn on the microcontroller and set the input you wish to encrypt using the switches. If you wish to randomize the key and the “n” value, press the up button the desired number of times. Using the down arrow, verify that the device is in encryption mode, indicated by a red flashing LED. Press the center button to perform the encryption. The output will be displayed on the LEDs. If you wish to decrypt the ciphertext, press the right or left button and verify that the device is in decryption mode by the blue flashing LED. Press the center button, and the LEDs will now show the original plaintext. DO NOT press the up button between encryption and decryption of the plaintext will be unrecoverable.
