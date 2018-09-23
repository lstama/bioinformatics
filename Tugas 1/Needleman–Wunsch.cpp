#include <bits/stdc++.h>
using namespace std;
int mx[256][256];
int blosum[256][256];
int before[256][256][2];

void create_blosum_mat(){
    ifstream myReadFile;
    myReadFile.open("blosum62.txt");
    string char_list;
    if (myReadFile.is_open()) {
        myReadFile >> char_list;
        for (int i = 0; i < char_list.length(); i++){
            char char_now;
            myReadFile >> char_now;
            while (char_now < 65 || char_now > 90) myReadFile >> char_now;
            for (int j = 0; j < char_list.length(); j++){
                myReadFile >> blosum[char_list[j]][char_now];
            }
        }
    }
    myReadFile.close();
}

void reset_states(){
    int default_value = -999999;
    for (int i = 0; i < 256; i++){
        for (int j = 0; j < 256; j++){
            mx[i][j] = default_value;
            before[i][j][0] = default_value;
            before[i][j][1] = default_value;
        }
    }
    mx[0][0] = 0;
    before[0][0][0] = -1;
    before[0][0][1] = -1;
    for (int i = 1; i < 256; i++){
        mx[0][i] = mx[0][i-1] - 6;
        before[0][i][0] = 0;
        before[0][i][1] = i-1;
        mx[i][0] = mx[i-1][0] - 6;
        before[i][0][0] = i-1;
        before[i][0][1] = 0;
    }
}

int main(){
    create_blosum_mat();
    reset_states();

    string a,b;
    cout << "Input first string : ";
    cin >> a;
    cout << "Input second string : ";
    cin >> b;

    for (int i = 1; i < b.length()+1; i++){
        for (int j = 1; j < a.length()+1; j++){
            int ans;
            //dari atas
            ans = mx[i-1][j] - 4;
            if (ans > mx[i][j]){
                mx[i][j] = ans;
                before[i][j][0] = i-1;
                before[i][j][1] = j;
            }
            //dari samping
            ans = mx[i][j-1] - 4;
            if (ans > mx[i][j]){
                mx[i][j] = ans;
                before[i][j][0] = i;
                before[i][j][1] = j-1;
            }
            //dari diagonal
            ans = mx[i-1][j-1] + blosum[b[i-1]][a[j-1]];//karena character mulai dari 0
            if (ans > mx[i][j]){
                mx[i][j] = ans;
                before[i][j][0] = i-1;
                before[i][j][1] = j-1;
            }
        }
    }

    // Output matrix hasil algoritma
    for (int i = 0; i < b.length()+1; i++){
        for (int j = 0; j < a.length()+1; j++){
            cout << '(' << mx[i][j] << ')' << ' ';
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < b.length()+1; i++){
        for (int j = 0; j < a.length()+1; j++){
            cout << '(' << before[i][j][0] << ',' << before[i][j][1] << ')' << ' ';
        }
        cout << endl;
    }

    // Backtracking
    string atas;
    string bawah;
    int now_i = b.length();
    int now_j = a.length();
    int a_now = a.length()-1;
    int b_now = b.length()-1;
    int now = 0;
    while ((now_i != 0) || (now_j != 0)){
        if (before[now_i][now_j][0] == now_i - 1){
            bawah = bawah + (b[b_now]);
            b_now--;
        } else {
            bawah = bawah + ('_');
        }
        if (before[now_i][now_j][1] == now_j - 1){
            atas = atas + (a[a_now]);
            a_now--;
        } else {
            atas = atas + ('_');
        }
        int temp = now_i;
        now_i = before[now_i][now_j][0];
        now_j = before[temp][now_j][1];
    }

    // Output hasil
    for (int i = atas.length()-1; i > -1 ; i--){
        cout << atas[i];
    }
    cout << endl;
    for (int i = bawah.length()-1; i > -1 ; i--){
        cout << bawah[i];
    }
    cout << endl;
}
