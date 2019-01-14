import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)
app.jinja_env.globals.update(usd=usd)

# Ensure templates are auto-reloaded


app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db", foreign_keys=True)


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Select the user's cash balance
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    user_cash = cash[0]["cash"]
    # Iterate over all of the user's stocks to display user's total cash
    holdings = db.execute("SELECT holding FROM owned WHERE user_id = :user_id", user_id=session["user_id"])
    holdings_sum = 0
    for i in range(len(holdings)):
        # Add the stocks value
        holdings_sum += float(holdings[i]["holding"])

    total_cash = usd(holdings_sum + user_cash)
    # Select all the user's stock from the owned table, where it will be displayed through jinja
    table_info = db.execute("SELECT * FROM owned WHERE user_id = :user_id", user_id=session["user_id"])
    return render_template("index.html", table_info=table_info, user_cash=user_cash, total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Ensures the user submited the form
    if request.method == "POST":
        # Ensures that the user selected a symbol
        if not request.form.get("symbol"):
            return apology("Please select a stock to buy")
        # Ensures that the user selected the number of shares
        if not request.form.get("shares"):
            return apology("Please select the number of shares")
        # Ensures that the user's input is a positive integer
        try:
            stockshares = int(request.form.get("shares"))
        except ValueError:
            return apology("Select a integer number")
        if stockshares <= 0:
            return apology("Please select the number of shares")
        # Lookup the values of the stock based on its symbol
        stock = lookup(request.form.get("symbol"))
        # Ensures that the input symbol is valid
        if not stock:
            return apology("There is no stock with that name")
        # Ensure that the user has enough money
        total_sum = stock["price"] * stockshares
        balance = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session["user_id"])
        user_cash = balance[0]["cash"]
        if total_sum > user_cash:
            return apology("You don't have enough money :(")
        else:
            """Execute Sqlite3 querrys to insert rows or update databases"""
            # Update the user's cash
            user_cash -= total_sum
            db.execute("UPDATE users SET cash = :user_cash WHERE id = :userid", user_cash=user_cash, userid=session["user_id"])
            # Put the stock's values into variables
            stockprice = stock["price"]
            stockname = stock["name"]
            stocksymbol = stock["symbol"]
            # Insert the acquisition in the portfolio table
            db.execute("INSERT INTO portfolio (user_id, stockname, stocksymbol, stockshares, stockprice, holding) VALUES(:user_id, :stockname, :stocksymbol, :stockshares, :stockprice, :holding)",
                       user_id=session["user_id"], stockname=stockname, stocksymbol=stocksymbol, stockshares=stockshares, stockprice=stockprice, holding=total_sum)
            # Update the owned table
            owned = db.execute("SELECT * FROM owned WHERE user_id = :user_id AND stocksymbol = :stocksymbol",
                               user_id=session["user_id"], stocksymbol=stocksymbol)
            if not owned:
                db.execute("INSERT INTO owned (user_id, stockname, stocksymbol, stockshares, stockprice, holding) VALUES(:user_id, :stockname, :stocksymbol, :stockshares, :stockprice, :holding)",
                           user_id=session["user_id"], stockname=stockname, stocksymbol=stocksymbol, stockshares=stockshares, stockprice=stockprice, holding=total_sum)
            else:
                p_shares = owned[0]["stockshares"]
                n_shares = p_shares + stockshares
                n_holding = n_shares * stockprice
                db.execute("UPDATE owned SET stockshares = :n_shares WHERE user_id = :user_id AND stocksymbol = :stocksymbol",
                           n_shares=n_shares, user_id=session["user_id"], stocksymbol=stocksymbol)
                db.execute("UPDATE owned SET holding = :n_holding WHERE user_id = :user_id AND stocksymbol = :stocksymbol",
                           n_holding=n_holding, user_id=session["user_id"], stocksymbol=stocksymbol)

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Select the portfolio table where it is stored what the user bought and sold
    table_info = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])

    return render_template("history.html", table_info=table_info)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # Ensures that the user submited the form
    if request.method == "POST":
        # Ensures that the user selected a symbol
        if not request.form.get("symbol"):
            return apology("No stock selected!")
        # Validates the user input
        search = lookup(request.form.get("symbol"))
        if not search:
            return apology("No stock found!")
        else:
            return render_template("quote_display.html", name=search["name"], symbol=search["symbol"], price=usd(search["price"]))
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    new_name = request.form.get("username")
    new_psswd = request.form.get("password")
    confirm_psswd = request.form.get("confirmation")
    # Ensures that the user submited the form
    if request.method == "POST":
        # Validates the user's inputs
        if not new_name:
            return apology("Missing username!")
        if not new_psswd:
            return apology("Missing password!")
        if not confirm_psswd:
            return apology("You must confirm your password!")
        # Ensures that the passwords match
        if new_psswd != confirm_psswd:
            return apology("Password doesn't match!")
        # Hash the password
        hash_psswd = generate_password_hash(new_psswd)
        # Insert the user's info into the users table
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hashed)", username=new_name, hashed=hash_psswd)
        # Ensures that there are no duplicate usernames
        if not result:
            return apology("Username already exists")
        # After registering store the user's id in session
        session["user_id"] = result
    else:
        return render_template("register.html")

    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Make sure to display only the shares already owned
    symbols = []
    t_info = db.execute("SELECT * FROM owned WHERE user_id = :user_id", user_id=session["user_id"])
    for j in range(len(t_info)):
        temp = t_info[j]["stocksymbol"]
        symbols.append(temp)
    # Ensures that the user submited the form
    if request.method == "POST":
        # Stores the user's input
        num_shares = int(request.form.get("shares"))
        stock_symbol = request.form.get("symbol")
        # Ensures that the number of shares exists and is bigger than 0
        if not num_shares or num_shares <= 0:
            return apology("Select the number of shares")
        # Stores the old number of shares of a particular stock
        o_shares = db.execute("SELECT stockshares FROM owned WHERE user_id = :user_id AND stocksymbol = :stock_symbol",
                              user_id=session["user_id"], stock_symbol=stock_symbol)
        ow_shares = o_shares[0]["stockshares"]

        stock = lookup(stock_symbol)
        # Ensures that the user can only sell what he possesses
        if num_shares > ow_shares:
            return apology("You don't have that many shares")
        else:
            # Stores the stock to be sold
            stockprice = stock["price"]
            stockname = stock["name"]
            stocksymbol = stock_symbol
            # Updates the new values for holding and shares
            holding = stock["price"] * num_shares
            stockshares = 0 - num_shares
            # Insert the sell into the portfolio table
            db.execute("INSERT INTO portfolio (user_id, stockname, stocksymbol, stockshares, stockprice, holding) VALUES(:user_id, :stockname, :stocksymbol, :stockshares, :stockprice, :holding)",
                       user_id=session["user_id"], stockname=stockname, stocksymbol=stocksymbol, stockshares=stockshares, stockprice=stockprice, holding=holding)
            # Update the user's cash
            o_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
            cash = o_cash[0]["cash"] + holding
            db.execute("UPDATE users SET cash = :user_cash WHERE id = :userid", user_cash=cash, userid=session["user_id"])
            # Update the number of shares and the holding
            n_shares = ow_shares + stockshares
            if n_shares == 0:
                db.execute("DELETE FROM owned WHERE user_id = :user_id AND stocksymbol = :stocksymbol",
                           user_id=session["user_id"], stocksymbol=stocksymbol)
            else:
                n_holding = n_shares * stockprice
                db.execute("UPDATE owned SET stockshares = :n_shares WHERE user_id = :user_id AND stocksymbol = :stocksymbol",
                           n_shares=n_shares, user_id=session["user_id"], stocksymbol=stocksymbol)
                db.execute("UPDATE owned SET holding = :n_holding WHERE user_id = :user_id AND stocksymbol = :stocksymbol",
                           n_holding=n_holding, user_id=session["user_id"], stocksymbol=stocksymbol)

        return redirect("/")

    else:
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
