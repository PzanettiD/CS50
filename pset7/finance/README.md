# Objective:
Implement a website via which users can "buy" and "sell" stocks.
## Requirements:
- Complete the implementation of register
  - Require that a user input a username.
  - Require that a user input a password, and then ask for password confirmation.
  - Submit the user’s input via POST to /register. 
  - INSERT the new user into users (sqlite3 table), storing a hash of the user’s password, not the password itself.
- Complete the implementation of quote in such a way that it allows a user to look up a stock’s current price.
  - Require that a user input a stock’s symbol.
  - Submit the user’s input via POST to /quote.
- Complete the implementation of buy in such a way that it enables a user to buy stocks.
  - Require that a user input a stock’s symbol.
  - Require that a user input a number of shares.
  - Submit the user’s input via POST to /buy.
  - Add one or more table to finance.db via which to keep track of the purchase. Store enough information so that you know who bought what at what price and when.
- Complete the implementation of index in such a way that it displays an HTML table summarizing, for the user currently logged in, which stocks the user owns, the numbers of shares owned, the current price of each stock, and the total value of each holding (i.e., shares times price). Also display the user’s current cash balance along with a grand total (i.e., stocks' total value plus cash).
- Complete the implementation of sell in such a way that it enables a user to sell shares of a stock (that he or she owns).
  - Require that a user input a stock’s symbol, implemented as a select menu.
  - Require that a user input a number of shares.
  - Submit the user’s input via POST to /sell.

