import math

def radius(r):
    print(f"radius = {r ** 2 * math.pi}")


def noat(amount): 
    print(f"amount = {amount / 110 * 100}")

# 1.8 * cels  + 32
def to_celsium(f):
    print(f"celsium is {(f - 32) * 5 / 9}")

def digit(number):
    count = 0
    while number != 0:
        count += 1
        number //= 10

    print(f"digit count is {count}")

def leap_year(date):
    if (date % 4 == 0 and date % 100 != 0) or (date % 100 == 0 and date % 400 == 0):
        print(f"{date} is leap  year")
        return True
    else:
        return False


radius(int(input("radius: ")))
noat(int(input("noat: ")))
if leap_year(int(input("check year is leap year: "))):
    print("yes")
else:
    print(f"not leap  year")

digit(int(input("count digit number: ")))
to_celsium(int(input("faranheit: ")))

for i in range(2025, 2101):
    leap_year(i)

