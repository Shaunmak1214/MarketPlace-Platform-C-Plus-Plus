# <p align="center">Hello, there CODERS !!! I'm Shaun ... <img src="https://raw.githubusercontent.com/MartinHeinz/MartinHeinz/master/wave.gif" width="30px"></p>

---

## <p align="center">:raised_hand:Basic Explanation of Program:</p>

### This program acts just same like a web version marketplace, that being said there will be two sides of the program, the owner and the shopper. 
####  - :older_man:Owner will be able to Upload, Delete, Update multiple products and also view an analyzed sales table.
####  - :boy:Shopper will be able to Shop thru the items the owner provides, add the items to a cart and make a payment.

### Note:
##### - The owner part and the shopper part is written in two different cpp file.
##### - All of the datas are stored in text files.

---

## <p align="center">:camera:Screenshots of Program working:</p>

### What owner will see:

#### :one: Menu of program 
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/menu.png">

#### :two: Owner Registration
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/ownerRegistration.png">

#### :three: Owner Registered
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/ownerRegistered.png">

#### :four: Proof of owner has been registered (.txt)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/ownerRegisteredtxt.png">

#### :five: Owner Login
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/ownerLogin.png">

#### :six: Owner Logged In (Re-directed to main menu)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/ownerLoggedIn.png">

#### :seven: Updating Owner Account
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/ownerAccountUpdate.png">

#### :eight: Proof of owner account has been updated (.txt)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/ownerAccountUpdatetxt.png">

#### :nine: Sales Analyzing (Picture 1, will prompt out the sales for every types of item)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/salesAnalyze1.png">

#### :one::zero: Sales Analyzing (Picture 2)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/salesAnalyze2.png">

#### :one::one: Item Navigation 1 (Navigate between items, in this case Magazine, Movies, Books)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/itemNav1.png">

#### :one::two: Item Navigation 2
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/itemNav2.png">

#### :one::three: Item Navigation 3
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/itemNav3.png">

#### :one::four: Item Adding (In this case, owner decides to add a magazine item)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/addItem.png">

#### :one::five: Updating the item details (We'll be updating the item we added just now)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/updateItem.png">

#### :one::six: Proof of item being updated
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/updateItemtxt.png">

#### :one::seven: Deleteing of an item (We'll be deleting the item we updated just now)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/deleteItem.png">

#### :one::eight: Proof of item being deleted
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/deleteItemtxt.png">

#### :one::nine: Displaying every item in the database (Magazine only since we are in the magazine tab)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/itemDisplay.png">

#### :two::zero: Displaying sales of a specific type of item (Displaying sales for magazine only)
### <img src = "https://github.com/Shaunmak1214/MarketPlace-Platform-C-Plus-Plus/blob/master/Screenshots/salesDisplay.png">

---

## <p align="center">:raised_hand:Delimter Concepts Explained:</p>

### Problem: 
#### Datas are stored in a table style format in a .txt file (example: figure 1.1). It is impossible to extract data by columns without the delimiter concepts used here. I will explain what i meant, refer to (figure 1.2). For this project, i'm using getline method to retrieve every lines from the txt file, since the txt file are formatted to a table looking style, there will be "impurites"...in this case the "|" to seperate every columns. Impurities = "|".

### Solution (uses of delimeter):
#### string delimeter = "|"
#### - First, getline is used to retrive every lines one by one from the text file.
#### - Second, for every line, i used the string.find function to find out all of the position of the "|" in the line and store the position in an array.
#### - Third, now i have all the "|" position for every line. So, to extract data, i used the string.substr function as the functions takes the value of the first parameter of the function as the starting point of the line and takes the value of the second parameter as the length of the space it needs to read. 
#### - Forth, with all the position stored inside an array, extracting a specific column of data seems easy. For example, lets say, you are trying to extract the data from the first column of the line, the data will be in between the first "|" and the second "|" found. So, with that being said, use the .substr function and pass the position of the first "|" as the first parameter and pass (the position of the second "|" minus the position of the first "|" found, that way you find out the exact space of the column) as the second parameter.
#### - Fifth, save the data found from the .substr function in a string variable.
#### - DONE !!!

