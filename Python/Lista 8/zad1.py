from matplotlib import pyplot as plt, animation
import random


board_size = 10
snake_x = []
snake_y = []
blocks_x = [random.randrange(1, board_size, 1) for _ in range(board_size)]
blocks_y = [random.randrange(1, board_size, 1) for _ in range(board_size)]
fig = plt.figure()
ax = plt.axes(xlim=(0, board_size), ylim=(0, board_size))
line, = ax.plot([], [], lw=2)


def init():
    plt.scatter(blocks_x, blocks_y)
    start_x = random.randrange(1, board_size, 1)
    start_y = random.randrange(1, board_size, 1)
    while (start_x, start_y) in zip(blocks_x, blocks_y):
        start_x = random.randrange(1, board_size, 1)
        start_y = random.randrange(1, board_size, 1)
    snake_x.insert(0, start_x)
    snake_y.insert(0, start_y)
    line.set_data(snake_x, snake_y)
    return line,


def move_snake(_i):
    if len(snake_x) == 5:
        snake_y.pop()
        snake_x.pop()
    current_x = snake_x[0]
    current_y = snake_y[0]
    possible_x = [current_x, current_x, current_x + 1, current_x - 1]
    possible_y = [current_y + 1, current_y - 1, current_y, current_y]

    new_position = random.randrange(0, len(possible_y))
    new_x = possible_x[new_position]
    new_y = possible_y[new_position]
    while ((new_x, new_y) in zip(snake_x, snake_y) or new_x not in range(0, board_size) or
            new_y not in range(0, board_size)):
        possible_y.remove(new_y)
        possible_x.remove(new_x)
        new_position = random.randrange(0, len(possible_y))
        new_x = possible_x[new_position]
        new_y = possible_y[new_position]

    snake_x.insert(0, new_x)
    snake_y.insert(0, new_y)

    for (x, y) in zip(snake_x, snake_y):
        if (x, y) in zip(blocks_x, blocks_y):
            print("KONIEC GRY")
            ani.event_source.stop()

    line.set_data(snake_x, snake_y)
    return line,


init()
ani = animation.FuncAnimation(fig, move_snake,  interval=500, blit=True)
plt.show()
