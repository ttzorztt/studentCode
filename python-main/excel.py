import openpyxl
import csv
from openpyxl.reader import excel
def open_excel():
    excel_file = openpyxl.load_workbook('test.xlsx')
    csv_file = csv.reader('test.csv')
    rows = [row[0] for row in csv_file]
    print(rows)
    first = excel_file.worksheets[0]
    # first['A1'].value = 12
    # first['A2'].value = 'f'
    # first.cell(row=1,column=2).value = 123
    excel_file.save('test.xlsx')
open_excel()