#include <iostream>
#include<vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <time.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GRID_SIZE = 20;
const int SNAKE_SIZE = 20;
const int BONUS_SIZE = 20;
const int OBSTACLE_WIDTH = 20;
const int OBSTACLE_HEIGHT = 500;


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

struct Point {
    int x, y;
};

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

struct Snake {
    Point head;
    std::vector<Point> body;
    Direction direction;
};

struct Food {
    Point position;
    bool isBonus;
};

struct Obstacle {
    Point position;
};
// Define a second obstacle
Obstacle obstacle2;
int score = 0;
int bonusScore = 0;
int bonusTimer = 0;
int regularFoodCounter = 0;
// Add a new variable for bonus food timer
int bonusSpawnTimer = 0;
const int BONUS_TIME_DURATION = 4000;  // Duration of bonus time in milliseconds
bool isGameOver = false;
Snake snake;
Food food;
Obstacle obstacle;
void spawnFood();

void initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Set the window background color
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
    SDL_RenderClear(renderer);

    snake.head = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    snake.direction = RIGHT;

    // Initialize the snake with an empty body
    snake.body.clear();

    food.position = { 0, 0 };  // Initialize at an invalid position
    spawnFood();

      obstacle.position = { rand() % (SCREEN_WIDTH / GRID_SIZE) * GRID_SIZE, rand() % (SCREEN_HEIGHT / GRID_SIZE) * GRID_SIZE }; // Change the obstacle position as needed
      obstacle2.position = { rand() % (SCREEN_WIDTH / GRID_SIZE) * GRID_SIZE, rand() % (SCREEN_HEIGHT / GRID_SIZE) * GRID_SIZE };
}

void spawnBonusFoods() {
    // Generate 10 bonus foods
    for (int i = 0; i < 10; ++i) {
        Food bonusFood;
        do {
            bonusFood.position.x = rand() % (SCREEN_WIDTH / GRID_SIZE) * GRID_SIZE;
            bonusFood.position.y = rand() % (SCREEN_HEIGHT / GRID_SIZE) * GRID_SIZE;
        } while (bonusFood.position.x == snake.head.x && bonusFood.position.y == snake.head.y);

        bonusFood.isBonus = true;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Yellow color for bonus food
        SDL_Rect bonusRect = { bonusFood.position.x, bonusFood.position.y, BONUS_SIZE, BONUS_SIZE };
        SDL_RenderFillRect(renderer, &bonusRect);
        SDL_RenderPresent(renderer);

        // No delay for bonus foods

        // Add bonus food to the vector
        snake.body.push_back(bonusFood.position);
    }
}

void spawnFood() {
    srand(time(nullptr));

    do {
        food.position.x = rand() % (SCREEN_WIDTH / GRID_SIZE) * GRID_SIZE;
        food.position.y = rand() % (SCREEN_HEIGHT / GRID_SIZE) * GRID_SIZE;
    } while (food.position.x == snake.head.x && food.position.y == snake.head.y);

    food.isBonus = false;

    ++regularFoodCounter;

    // Check if it's time to spawn bonus food
    if (regularFoodCounter == 7) {
        regularFoodCounter = 0;  // Reset the counter
        food.isBonus = true;
        bonusTimer = BONUS_TIME_DURATION;  // Bonus food will be displayed for 4 seconds
    }
}

// Rest of the code remains the same...

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Render snake
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect snakeRect = { snake.head.x, snake.head.y, SNAKE_SIZE, SNAKE_SIZE };
    SDL_RenderFillRect(renderer, &snakeRect);

    for (const auto& bodyPart : snake.body) {
        SDL_Rect bodyRect = { bodyPart.x, bodyPart.y, SNAKE_SIZE, SNAKE_SIZE };
        SDL_RenderFillRect(renderer, &bodyRect);
    }

    // Render food
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect foodRect = { food.position.x, food.position.y, (food.isBonus ? BONUS_SIZE : SNAKE_SIZE), (food.isBonus ? BONUS_SIZE : SNAKE_SIZE) };
    SDL_RenderFillRect(renderer, &foodRect);

// Render obstacle as a tree
  // Render obstacle as a tree with increased size only on the y-axis
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // Dark green color for tree
    SDL_Rect obstacleRect = { obstacle.position.x, obstacle.position.y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT };
    SDL_RenderFillRect(renderer, &obstacleRect);
// Render the second obstacle
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect obstacle2Rect = { obstacle2.position.x, obstacle2.position.y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT };
    SDL_RenderFillRect(renderer, &obstacle2Rect);

    // Render bonus food if active
    if (food.isBonus) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Yellow color for bonus food
        SDL_Rect bonusRect = { food.position.x, food.position.y, BONUS_SIZE, BONUS_SIZE };
        SDL_RenderFillRect(renderer, &bonusRect);
    }

    SDL_RenderPresent(renderer);
}


void handleInput() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isGameOver = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (snake.direction != DOWN)
                        snake.direction = UP;
                    break;
                case SDLK_DOWN:
                    if (snake.direction != UP)
                        snake.direction = DOWN;
                    break;
                case SDLK_LEFT:
                    if (snake.direction != RIGHT)
                        snake.direction = LEFT;
                    break;
                case SDLK_RIGHT:
                    if (snake.direction != LEFT)
                        snake.direction = RIGHT;
                    break;
            }
            break;
    }
}
void move() {
    // Move the body
    for (int i = snake.body.size() - 1; i > 0; --i) {
        snake.body[i] = snake.body[i - 1];
    }

    // Update the first segment of the body to the current head position
    if (!snake.body.empty()) {
        snake.body[0] = snake.head;
    }

    // Move the head
    switch (snake.direction) {
        case UP:
            snake.head.y -= GRID_SIZE;
            break;
        case DOWN:
            snake.head.y += GRID_SIZE;
            break;
        case LEFT:
            snake.head.x -= GRID_SIZE;
            break;
        case RIGHT:
            snake.head.x += GRID_SIZE;
            break;
    }
    //moveObstacle();
}

void checkCollision() {
    // Check collision with walls and adjust snake position if necessary
    if (snake.head.x < 0) {
        snake.head.x = SCREEN_WIDTH - GRID_SIZE;
    } else if (snake.head.x >= SCREEN_WIDTH) {
        snake.head.x = 0;
    } else if (snake.head.y < 0) {
        snake.head.y = SCREEN_HEIGHT - GRID_SIZE;
    } else if (snake.head.y >= SCREEN_HEIGHT) {
        snake.head.y = 0;
    }

    // Check collision with itself
    for (const auto& bodyPart : snake.body) {
        if (snake.head.x == bodyPart.x && snake.head.y == bodyPart.y) {
            isGameOver = true;
            return;
        }
    }

// Check collision with food, including bonus food
  // Check collision with food, including bonus food
   // Check collision with food, including bonus food
    if ((snake.head.x == food.position.x && snake.head.y == food.position.y) ||
        (food.isBonus && snake.head.x == food.position.x && snake.head.y == food.position.y)) {
        score += (food.isBonus ? 10 : 1);
        if (food.isBonus) {
            bonusScore += 10;
            bonusTimer = 0;  // Reset bonus timer
        }
        snake.body.push_back({ -1, -1 });  // Dummy body part, will be updated in the next move
        spawnFood();
    }


    // Check collision with obstacle
    if ((snake.head.x >= obstacle.position.x && snake.head.x < obstacle.position.x + OBSTACLE_WIDTH &&
         snake.head.y >= obstacle.position.y && snake.head.y < obstacle.position.y + OBSTACLE_HEIGHT) ||
        (std::any_of(snake.body.begin(), snake.body.end(),
                     [&](const Point& bodyPart) {
                         return snake.head.x == bodyPart.x && snake.head.y == bodyPart.y;
                     }))) {
        isGameOver = true;
        return;
    }
}


void updateBonus() {
    if (bonusTimer > 0) {
        bonusTimer -= 16;  // 16 milliseconds per frame
    } else if (food.isBonus) {
        // Bonus time expired, convert bonus food back to regular food
        food.isBonus = false;
        // Spawn new regular food
        spawnFood();
    }
}


int main(int argc, char** args) {
    initialize();

    while (!isGameOver) {
        handleInput();
        move();
        //moveObstacle();  // Move the obstacle along with the snake
        checkCollision();
        updateBonus();
        render();
        SDL_Delay(200);  // Cap the frame rate to approximately 5 frames per second
    }

    // Game over, print scores
    std::cout << "Game Over!\n";
    std::cout << "Total Score: " << score << "\n";
    std::cout << "Bonus Score: " << bonusScore << "\n";

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
