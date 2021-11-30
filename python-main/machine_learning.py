# scikit-learn
# This package must be installed with pip before running this code
from numpy import log
import pandas
from sklearn.linear_model import LogisticRegression

def function_1():
    value = pandas.read_csv("test.csv")
    # print(value.head())
    factor = ["number"]
    ind = value.loc[:,factor]
    train = LogisticRegression()
    train.fit(ind,value.range)
    print(train.predict([[15]]))

def __main__():
    input_database = pandas.read_csv("date.csv") #  read the database named *.csv
    # You can uncomment this to show the first five rows of the database named input_database
    # print(input_database.head()) 
    factor = ["length","width"]
    Independent_variable = input_database.loc[:,factor]
    Dependent_variable = input_database.ret
    # train this model
    train = LogisticRegression()
    train.fit(Independent_variable,Dependent_variable)
    # print the predict
    Forecast_data = eval(input("Please enter the length and width of the banknotes you want to predict, separated by commas："))
    ret = train.predict([Forecast_data])
    print("It's {} yuan".format(ret))
# __main__()

def function_2():
    pass
function_1()