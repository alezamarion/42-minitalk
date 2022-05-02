
## Use:

🚧 Cloning:<br/>
```
git clone https://github.com/alezamarion/42-minitalk.git
cd 42-minitalk
make
```

🚧 Compiling:<br/>
```
First you launch server:
$ ./server
Server will print its PID and wait

So you use the client to send string or unicode characters to the server
$ ./client `PID_SERVER` `STRING`
```

## Subject

The purpose of this project is to code a small data exchange program using UNIX signals. <br>

**Mandatory Part** <br>
• You must create a communication program in the form of a client and server. <br> 
• The server must be launched first, and after being launched it must display its PID. <br>
• The client will take as parameters: <br>
◦ The server PID. <br>
◦ The string that should be sent. <br>
• The client must communicate the string passed as a parameter to the server. <br>
  &ensp; Once the string has been received, the server must display it. <br>
• Communication between your programs should ONLY be done using UNIX signals. <br>
• The server must be able to display the string pretty quickly. By quickly we mean that if you think it is too long, <br>
  &ensp; then it is probably too long (hint: 1 second   for 100 characters is COLOSSAL) <br>
• Your server should be able to receive strings from several clients in a row, without needing to be restarted. <br>
• You can only use the two signals SIGUSR1 and SIGUSR2. <br><br>

**Bonus** <br>
• The server confirms every signal received by sending a signal to the client. <br>
• Support Unicode characters! <br>
