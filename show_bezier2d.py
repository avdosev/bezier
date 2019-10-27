import json

with open('bezier2d.json') as file:
    data = json.load(file)
    x = [i[0] for i in data]
    y = [i[1] for i in data]


    import matplotlib.pyplot as plt

    plt.plot(x,y)

    plt.show()