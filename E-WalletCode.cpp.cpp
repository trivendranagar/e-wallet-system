#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Bank
{
public:
    static int bank;
    void bankBalance()
    {
        cout << "\n-----------------------------";
        cout << "\nAvailable fund in Bank : " << bank;
        cout << "\n-----------------------------\n";
    }
};
int Bank::bank = 10000;

// ---------- Transaction Record ----------
struct Transaction {
    string type;   // Add Money, Payment, Transfer
    int amount;
};

class PhonePe : public Bank
{
public:
    int ph = 0, temp;
    vector<Transaction> history;

    void addMoney()
    {
        cout << "Enter amount to add in PhonePe: ";
        cin >> temp;
        if (temp > bank)
        {
            cout << "\n Insufficient fund in bank\n";
        }
        else
        {
            bank -= temp;
            ph += temp;
            history.push_back({"Added Money", temp});
            cout << "\n Amount Added Successfully!\n";
        }
    }

    void makePayment()
    {
        cout << "\nEnter payment amount: ";
        cin >> temp;
        if (temp > ph)
        {
            cout << "\n Insufficient fund in PhonePe\n";
        }
        else
        {
            ph -= temp;
            history.push_back({"Payment", temp});
            cout << "\n Payment Done!\n";
        }
    }

    void transferToGooglePay(class GooglePay &gp);

    void checkBalance()
    {
        cout << "\nPhonePe Balance : ₹" << ph << endl;
    }

    void showHistory()
    {
        cout << "\n PhonePe Transaction History:\n";
        if(history.empty()){
            cout << "   No Transactions Yet!\n";
        }else{
            for (auto &t : history)
                cout << "   " << t.type << " : ₹" << t.amount << endl;
        }
    }
};

class GooglePay : public Bank
{
public:
    int gp = 0, temp;
    vector<Transaction> history;

    void addMoney()
    {
        cout << "Enter amount to add in GooglePay: ";
        cin >> temp;
        if (temp > bank)
        {
            cout << "\n Insufficient fund in bank\n";
        }
        else
        {
            bank -= temp;
            gp += temp;
            history.push_back({"Added Money", temp});
            cout << "\n Amount Added Successfully!\n";
        }
    }

    void makePayment()
    {
        cout << "\nEnter payment amount: ";
        cin >> temp;
        if (temp > gp)
        {
            cout << "\n Insufficient fund in GooglePay\n";
        }
        else
        {
            gp -= temp;
            history.push_back({"Payment", temp});
            cout << "\n Payment Done!\n";
        }
    }

    void transferToPhonePe(PhonePe &ph)
    {
        cout << "\nEnter amount to transfer PhonePe from GooglePay: ";
        cin >> temp;
        if (temp > gp)
        {
            cout << "\n Insufficient fund in GooglePay\n";
        }
        else
        {
            gp -= temp;
            ph.ph += temp;
            history.push_back({"Transfer to PhonePe", temp});
            ph.history.push_back({"Received from GooglePay", temp});
            cout << "\n Transfer Successful!\n";
        }
    }

    void checkBalance()
    {
        cout << "\nGooglePay Balance : ₹" << gp << endl;
    }

    void showHistory()
    {
        cout << "\n GooglePay Transaction History:\n";
        if(history.empty()){
            cout << "   No Transactions Yet!\n";
        }else{
            for (auto &t : history)
                cout << "   " << t.type << " : ₹" << t.amount << endl;
        }
    }
};

// ------------ Transfer function defined outside ------------
void PhonePe::transferToGooglePay(GooglePay &gp)
{
    cout << "\nEnter amount to transfer GooglePay from PhonePe: ";
    cin >> temp;
    if (temp > ph)
    {
        cout << "\n Insufficient fund in PhonePe\n";
    }
    else
    {
        ph -= temp;
        gp.gp += temp;
        history.push_back({"Transfer to GooglePay", temp});
        gp.history.push_back({"Received from PhonePe", temp});
        cout << "\n Transfer Successful!\n";
    }
}

int main()
{
    int choice, choice2;
    PhonePe *ph = new PhonePe();
    GooglePay *gp = new GooglePay();

    while (1)
    {
        cout << "\n=====================";
        cout << "\n   MAIN MENU ";
        cout << "\n=====================";
        cout << "\n1. Add Money";
        cout << "\n2. Make Payment";
        cout << "\n3. Check Wallet Balance";
        cout << "\n4. Check Bank Balance";
        cout << "\n5. Transfer Between Wallets";
        cout << "\n6. Show Transaction History";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\n1. Add Money in PhonePe";
            cout << "\n2. Add Money in GooglePay\n";
            cin >> choice2;
            if (choice2 == 1) ph->addMoney();
            else if (choice2 == 2) gp->addMoney();
        }
        else if (choice == 2)
        {
            cout << "\n1. Payment from PhonePe";
            cout << "\n2. Payment from GooglePay\n";
            cin >> choice2;
            if (choice2 == 1) ph->makePayment();
            else if (choice2 == 2) gp->makePayment();
        }
        else if (choice == 3)
        {
            cout << "\n1. Check PhonePe Balance";
            cout << "\n2. Check GooglePay Balance\n";
            cin >> choice2;
            if (choice2 == 1) ph->checkBalance();
            else if (choice2 == 2) gp->checkBalance();
        }
        else if (choice == 4)
        {
            Bank *b = new Bank();
            b->bankBalance();
        }
        else if (choice == 5)
        {
            cout << "\n1. Transfer PhonePe -> GooglePay";
            cout << "\n2. Transfer GooglePay -> PhonePe\n";
            cin >> choice2;
            if (choice2 == 1) ph->transferToGooglePay(*gp);
            else if (choice2 == 2) gp->transferToPhonePe(*ph);
        }
        else if (choice == 6)
        {
            cout << "\n1. PhonePe History";
            cout << "\n2. GooglePay History\n";
            cin >> choice2;
            if (choice2 == 1) ph->showHistory();
            else if (choice2 == 2) gp->showHistory();
        }
        else if (choice == 7)
        {
            cout << "\n Exiting... Thank you!\n";
            break;
        }
        else
        {
            cout << "\n Invalid Choice, Try Again!\n";
        }
    }
}
