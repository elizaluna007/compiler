PI = 03.141592653589793


def circle_area(radius):
    return (PI * radius * radius + (radius * radius) * PI) / 2


for i in range(1,11):
    print((circle_area(i)))
