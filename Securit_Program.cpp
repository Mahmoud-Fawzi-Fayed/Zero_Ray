// Zero_Ray
#include <iostream>
#include <string>
#include <iomanip>
#include<vector>
using namespace std;

// ASCII
// small from 65 to 90 : capital from 97 to 122
// space = 32
// Cipher

void encryption(char message[]) {
    int count = 0;
    cout << "Please enter a message to be encrypted:\n\n";
    cin.get(message[count]);

    while (message[count] != '\n') {
        count++;
        cin.get(message[count]);
    }

}
void decryption(char message[]) {
    int count = 0;
    cout << "Please enter a message to be decrypted:\n\n";
    cin.get(message[count]);

    while (message[count] != '\n') {
        count++;
        cin.get(message[count]);
    }

}
//transposition

class playfair {
public:
    string msg; char n[5][5];
    void play(string k, string t, bool m, bool e) {
        createEncoder(k, m);
        getText(t, m, e);
        if (e)
            play(1);
        else
            play(-1);
        print();
    }
private:
    void play(int dir) {
        int j, k, p, q;
        string nmsg;
        for (string::const_iterator it = msg.begin(); it != msg.end(); it++) {
            if (getPos(*it++, j, k))
                if (getPos(*it, p, q)) {
                    if (j == p) {
                        nmsg += getChar(j, k + dir);
                        nmsg += getChar(p, q + dir);
                    }
                    else if (k == q) {
                        nmsg += getChar(j + dir, k);
                        nmsg += getChar(p + dir, q);
                    }
                    else {
                        nmsg += getChar(p, k);
                        nmsg += getChar(j, q);
                    }
                }
        }
        msg = nmsg;
    }
    void print() {
        cout << "\n\n Solution:" << endl;
        string::iterator it = msg.begin(); int count = 0;
        while (it != msg.end()) {
            cout << *it;
            it++;
            cout << *it << " ";
            it++;
            if (++count >= 26)
                cout << endl;
            count = 0;
        }
        cout << endl << endl;
    }
    char getChar(int a, int b) {
        return n[(b + 5) % 5][(a + 5) % 5];
    }
    bool getPos(char l, int& c, int& d) {
        for (int y = 0; y < 5; y++)
            for (int x = 0; x < 5; x++)
                if (n[y][x] == l) {
                    c = x;
                    d = y;
                    return true;
                }
        return false;
    }
    void getText(string t, bool m, bool e) {
        for (string::iterator it = t.begin(); it != t.end(); it++) {
            //to choose J = I or no Q in the alphabet.
            *it = toupper(*it);
            if (*it < 65 || *it > 90)
                continue;
            if (*it == 'J' && m)
                *it = 'I';
            else if (*it == 'Q' && !m)
                continue;
            msg += *it;
        }
        if (e) {
            string nmsg = ""; size_t len = msg.length();
            for (size_t x = 0; x < len; x += 2) {
                nmsg += msg[x];
                if (x + 1 < len) {
                    if (msg[x] == msg[x + 1]) nmsg += 'X';
                    nmsg += msg[x + 1];
                }
            }
            msg = nmsg;
        }
        if (msg.length() & 1)
            msg += 'X';
    }
    void createEncoder(string key, bool m) {
        if (key.length() < 1)
            key = "KEYWORD";
        key += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string s = "";
        for (string::iterator it = key.begin(); it != key.end(); it++) {
            *it = toupper(*it);
            if (*it < 65 || *it > 90)
                continue;
            if ((*it == 'J' && m) || (*it == 'Q' && !m))
                continue;
            if (s.find(*it) == -1)
                s += *it;
        }
        copy(s.begin(), s.end(), &n[0][0]);
    }
};
//play fair

string encryptionMessage(string Msg)
{
    string CTxt = "";
    int a = 3;
    int b = 6;
    for (int i = 0; i < Msg.length(); i++)
    {
        CTxt = CTxt + (char)((((a * Msg[i]) + b) % 26) + 65);
    }
    return CTxt;
}
string decryptionMessage(string CTxt)
{
    string Msg = "";
    int a = 3;
    int b = 6;
    int a_inv = 0;
    int flag = 0;
    for (int i = 0; i < 26; i++)
    {
        flag = (a * i) % 26;
        if (flag == 1)
        {
            a_inv = i;
        }
    }
    for (int i = 0; i < CTxt.length(); i++)
    {
        Msg = Msg + (char)(((a_inv * ((CTxt[i] - b)) % 26)) + 65);
    }
    return Msg;
} //affine tech
//affine tech

void getKeyMatrix(string key, int keyMatrix[][3])
{
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}

void encrypt(int cipherMatrix[][1],
    int keyMatrix[][3],
    int messageVector[][1])
{
    int x, i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            cipherMatrix[i][j] = 0;

            for (x = 0; x < 3; x++)
            {
                cipherMatrix[i][j] +=
                    keyMatrix[i][x] * messageVector[x][j];
            }

            cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
        }
    }
}
void HillCipher(string message, string key)
{
    int keyMatrix[3][3];
    getKeyMatrix(key, keyMatrix);

    int messageVector[3][1];

    for (int i = 0; i < 3; i++)
        messageVector[i][0] = (message[i]) % 65;

    int cipherMatrix[3][1];

    encrypt(cipherMatrix, keyMatrix, messageVector);

    string CipherText;

    for (int i = 0; i < 3; i++)
        CipherText += cipherMatrix[i][0] + 65;

    cout << " Ciphertext:" << CipherText;
}
//hill cipher

string One_Time_Pad_Encription(string plainText, string keyvalues) {
    string withoutSpacePlainText = "";
    string withoutSpaceKeyvalues = "";
    for (int i = 0; i < plainText.size(); i++) {
        if ((plainText[i] >= 'A' && plainText[i] <= 'Z') || (plainText[i] >= 'a' && plainText[i] <= 'z')) {
            withoutSpacePlainText += toupper(plainText[i]);
        }
    }
    for (int i = 0; i < keyvalues.size(); i++) {
        if ((keyvalues[i] >= 'A' && keyvalues[i] <= 'Z') || (keyvalues[i] >= 'a' && keyvalues[i] <= 'z')) {
            withoutSpaceKeyvalues += toupper(keyvalues[i]);
        }
    }
    int ln1 = withoutSpacePlainText.size();
    int ln2 = withoutSpaceKeyvalues.size();
    string newKeyValues = "", finalKeyValues = "";
    if (ln1 > ln2) {
        int extra = ln1 - ln2;

        int extratime = extra / ln2;
        if (extra % ln2 != 0) extratime++;

        int cnt = 0;
        while (cnt <= extratime) {
            for (int i = 0; i < ln2; i++) {
                newKeyValues += withoutSpaceKeyvalues[i];
            }
            cnt++;
        }
        for (int i = 0; i < ln1; i++) {
            finalKeyValues += newKeyValues[i];
        }
    }
    else if (ln1 <= ln2) {
        for (int i = 0; i < ln1; i++) {
            finalKeyValues += withoutSpaceKeyvalues[i];
        }
    }
    string ansCipherText = "";
    for (int i = 0; i < ln1; i++) {
        int sum = ((withoutSpacePlainText[i] - 'A') + (finalKeyValues[i] - 'A') + 1) % 26;
        ansCipherText += (sum + 'A');
    }
    cout << "Plain Text : Key Text ..." << endl;
    cout << withoutSpacePlainText << " " << finalKeyValues << endl;
    return ansCipherText;
}
//one time pad

long long int func(long long int g, long long int h,
    long long int Ps)
{
    if (h == 1)
        return g;

    else
        return (((long long int)pow(g, h)) % Ps);
}
//diffi-helman

int main(int argc, char* argv[])
{
    int m = 1;
    while ( true ) {
        int q;
        
        cout << "Zero_Ray" << endl;
        cout << "\nWelcome to Security program\n" << endl;
        cout << "1. Cipher" << endl << "2. transpoition" << endl << "3. play fair" << endl << "4. simple shift vig" << endl << "5. full vig" << endl << "6. affine" << endl << "7. hill cipher" << endl << "8. one time pad" << endl << "9. diffe-helman" << endl << "10. quit" << endl << "Enter choice: ";
        cin >> q;
        if (q == 1) {
            int choice;
            cout << "\n1. Encryption" << endl << "2. Decryption" << endl << "Enter choice: ";
            cin >> choice;
            cin.ignore();
            if (choice == 1) {
                // encryption
                string msg;
                cout << "Message can only be alphabetic" << endl;
                cout << "Enter message: ";
                getline(cin, msg);

                int key;
                cout << "Enter key (0-25): ";
                cin >> key;
                cin.ignore();

                string encryptedText = msg;

                for (int i = 0; i < msg.size(); i++) {

                    if (msg[i] == 32) {
                        continue; //32 is ASCII of space character, we will ignore it
                    }
                    else {

                        if ((msg[i] + key) > 122) {
                            //after lowercase z move back to a, z's ASCII is 122
                            int temp = (msg[i] + key) - 122;
                            encryptedText[i] = 96 + temp;
                        }
                        else if (msg[i] + key > 90 && msg[i] <= 96) {
                            //after uppercase Z move back to A, 90 is Z's ASCII
                            int temp = (msg[i] + key) - 90;
                            encryptedText[i] = 64 + temp;
                        }
                        else {
                            //in case of characters being in between A-Z & a-z
                            encryptedText[i] += key;
                        }
                    } //if
                } // for

                cout << "Encrypted Message: " << encryptedText<<endl;
            }
            else if (choice == 2) {
                //decryption

                string encpMsg;
                cout << "Message can only be alphabetic" << endl;
                cout << "Enter encrypted text: ";
                getline(cin, encpMsg);

                int dcyptKey;
                cout << "Enter key (0-25): ";
                cin >> dcyptKey;
                cin.ignore();

                string decryptedText = encpMsg;

                for (int i = 0; i < encpMsg.size(); i++) {
                    if (encpMsg[i] == 32) {
                        continue; //ignoring space
                    }
                    else {
                        if ((encpMsg[i] - dcyptKey) < 97 && (encpMsg[i] - dcyptKey) > 90) {
                            int temp = (encpMsg[i] - dcyptKey) + 26;
                            decryptedText[i] = temp;
                        }
                        else if ((encpMsg[i] - dcyptKey) < 65) {
                            int temp = (encpMsg[i] - dcyptKey) + 26;
                            decryptedText[i] = temp;
                        }
                        else {
                            decryptedText[i] = encpMsg[i] - dcyptKey;
                        }
                    }
                }

                cout << "Decrypted Message: " << decryptedText << endl;

            }
            else {
                cout << "Invalid choice";
            }

        }       //      
        else if (q == 2) {
            int ans = 0;
            char message[100];

            while (ans != 3) {
                cout << "1. Encrypt a message.\n2. Decrypt a message.\n3. Quit\n";
                cin >> ans;

                if (ans == 1) {
                    cout << "Enter yput message: ";
                    cin >> message;
                    encryption(message);
                }

                if (ans == 2) {
                    cout << "Enter yput message: ";
                    cin >> message;
                    decryption(message);
                }

                if (ans == 3) {
                    break;
                }
            }
            return 0;
        }
        else if (q == 3) {
            string k, i, msg;
            bool m, c;
            cout << "1. Encrpty " << endl << "2. Decypt" << endl;
            getline(cin, i);
            c = (i[0] == 1);
            cout << "Enter a key: ";
            getline(cin, k);
            cout << "I <-> J (Y/N): ";
            getline(cin, i);
            m = (i[0] == 2);
            cout << "Enter the message: ";
            getline(cin, msg);
            playfair pf;
            pf.play(k, msg, m, c);
            return system("pause");

        }
        else if (q == 4) {
            char message[100], ch;
            int i, key, p;
            cout << "\n1. Encryption" << endl << "2. Decryption" << endl << "Enter choice: ";
            cin >> p;
            if (p == 1) {
                cout << "Enter a message to encrypt: ";
                cin.getline(message, 100);
                cout << "Enter key: ";
                cin >> key;
                for (i = 0; message[i] != '\0'; ++i) {
                    ch = message[i];
                    if (ch >= 'a' && ch <= 'z') {
                        ch = ch + key;
                        if (ch > 'z') {
                            ch = ch - 'z' + 'a' - 1;
                        }
                        message[i] = ch;
                    }
                    else if (ch >= 'A' && ch <= 'Z') {
                        ch = ch + key;
                        if (ch > 'Z') {
                            ch = ch - 'Z' + 'A' - 1;
                        }
                        message[i] = ch;
                    }
                }
                cout << "Encrypted message: " << message;
                return 0;
            }
            else if (p == 2) {
                cout << "Enter a message to decrypt: ";
                cin.getline(message, 100);
                cout << "Enter key: ";
                cin >> key;
                for (i = 0; message[i] != '\0'; ++i) {
                    ch = message[i];
                    if (ch >= 'a' && ch <= 'z') {
                        ch = ch - key;
                        if (ch < 'a') {
                            ch = ch + 'z' - 'a' + 1;
                        }
                        message[i] = ch;
                    }
                    else if (ch >= 'A' && ch <= 'Z') {
                        ch = ch - key;
                        if (ch > 'a') {
                            ch = ch + 'Z' - 'A' + 1;
                        }
                        message[i] = ch;
                    }
                }
                cout << "Decrypted message: " << message;
                return 0;
            }
        }
        else if (q == 5) {
            int i, j, k, n;
            int l;
            cout << "\n1. Encryption" << endl << "2. Decryption" << endl << "Enter choice: ";
            cin >> l;
            vector<vector<char> > a(26, vector<char>(26));
            k = 0;
            n = 26;
            for (i = 0; i < n; i++) {
                k = i;
                for (j = 0; j < n; j++) {
                    a[i][j] = 'A' + k;
                    k++;
                    if (k == 26)
                        k = 0;
                }
            }
            cout << "Enter the message\n";
            string s;
            cin >> s;
            cout << "Enter the key\n";
            string key;
            cin >> key;
            k = 0;
            int mod = key.size();
            for (i = key.size(); i < s.size(); i++) {
                key += key[k % mod];
                k++;
            }
            if (l == 1) {
                string encrypt;
                for (i = 0; i < s.size(); i++) {
                    encrypt += a[s[i] - 'A'][key[i] - 'A'];
                }
                cout << "Encrypted message: " << encrypt << '\n';
                return 0;
            }
            else if (l == 2) {
                string decrypt;
                for (i = 0; i < s.size(); i++) {
                    for (j = 0; j < n; j++) {
                        if (a[j][key[i] - 'A'] == s[i]) {
                            decrypt += 'A' + j;
                            break;
                        }
                    }
                }
                cout << "Decrypted message: " << decrypt << '\n';
                return 0;
            }
        }
        else if (q == 6) {
            int k;
            cout << "\n1. Encryption" << endl << "2. Decryption" << endl << "Enter choice: ";
            cin >> k;
            cout << "Enter the message: ";
            string message;
            cin >> message;
            if (k == 1) {
                cout << "\nEncrypted Message is : " << encryptionMessage(message);
            }
            else if (k == 2) {
                cout << "\nDecrypted Message is: " << decryptionMessage(message);
            }
        }
        else if (q == 7) {
            string message = "ACT";

            string key = "GYBNQKURP";

            HillCipher(message, key);

            return 0;
        }
        else if (q == 8) {
            string plaintext, keyvalue;

            cout << "Enter Plain Text..." << endl;
            getline(cin, plaintext);

            cout << "Enter key values..." << endl;
            getline(cin, keyvalue);

            string ans = One_Time_Pad_Encription(plaintext, keyvalue);
            cout << "Cipher Text..." << endl;
            cout << ans << endl;

        }
        else if (q == 9) {
            long long int Ps, Gs, p, g, q, h, K_A, K_B;
            // Both persons agrees on public keys Gs and Ps
            Ps = 23; // A prime number Ps
            cout << "Value of Ps is: " << Ps << endl;

            Gs = 9; // Gs is primitive root for Ps
            cout << "Value of Gs is: " << Gs << endl;

            // g is the private key chosen by Joy
            g = 4; // The chosen private key is g
            cout << "Private key g is: " << g << endl;

            p = func(Gs, g, Ps); // fetches the generated key

            h = 3; // The chosen private key is h
            cout << "Private key h is: " << h << endl;

            q = func(Gs, h, Ps); // fetches the generated key

            // After the exchange of keys, generating the secret key
            K_A = func(q, g, Ps);
            K_B = func(p, h, Ps); 
            cout << "Joy's Secret key is: " << K_A << endl;
            cout << "Happy's Secret key is: " << K_B << endl;
            return 0;
        }
        else {
        break;
}
    }   
}
