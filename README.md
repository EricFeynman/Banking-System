# Bank Management System

A console-based bank management system implemented in C++. The program allows users to perform various banking operations, such as creating accounts, depositing and withdrawing money, checking balances, and more. The account information is stored in a CSV file (`database.csv`).

## Features

- **Create Account:** Users can create new bank accounts by providing necessary details such as account number, account holder's name, account type (Savings or Current), and initial deposit amount.

- **Deposit and Withdraw:** Users can deposit or withdraw money from their accounts. The program checks for minimum balance requirements for Savings and Current accounts.

- **Account Modification:** Users can modify account details, including the account holder's name, account type, and balance amount.

- **Account Deletion:** Users can close an existing account, removing it from the system.

- **Display Account Details:** Users can view the details of a specific account or display a list of all account holders.

## File Handling

The program uses file handling to persistently store account information in a CSV file (`database.csv`). Each line in the file represents an account with fields separated by commas.

