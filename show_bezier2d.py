import json

with open('bezier2d.json') as file:
    data = json.load(file)
    x = [i[0] for i in data]
    y = [i[1] for i in data]
    z = [i[2] for i in data]


    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D

    fig = plt.figure()
    ax = fig.gca(projection='3d')

    ax.plot(x, y, z)

    plt.show()