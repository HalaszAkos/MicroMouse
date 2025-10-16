#include <cstdlib>
#include <iostream>
#include <string>


bool wallFront() {
    std::cout << "wallFront" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

bool wallRight() {
    std::cout << "wallRight" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

bool wallLeft() {
    std::cout << "wallLeft" << std::endl;
    std::string response;
    std::cin >> response;
    return response == "true";
}

void moveForward(int distance = 1) {
    std::cout << "moveForward ";
    // Don't print distance argument unless explicitly specified, for
    // backwards compatibility with older versions of the simulator
    if (distance != 1) {
        std::cout << distance;
    }
    std::cout << std::endl;
    std::string response;
    std::cin >> response;
    if (response != "ack") {
        std::cerr << response << std::endl;
        throw;
    }
}

void turnRight() {
    std::cout << "turnRight" << std::endl;
    std::string ack;
    std::cin >> ack;
}

void turnLeft() {
    std::cout << "turnLeft" << std::endl;
    std::string ack;
    std::cin >> ack;
}

void setColor(int x, int y, char color) {
    std::cout << "setColor " << x << " " << y << " " << color << std::endl;
}

void setText(int x, int y, const std::string& text) {
    std::cout << "setText " << x << " " << y << " " << text << std::endl;
}

void log(const std::string& text) {
    std::cerr << text << std::endl;
}
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // For std::min
#include <cmath>     // For std::abs
#include <stdexcept> // For std::runtime_error
#include <optional>  // For std::optional (C++17 and later)
#include <chrono>    // For std::chrono
#include <thread>    // For std::this_thread::sleep_for

// Forward declaration of Cell to be used in class/function definitions
class Cell;

// Class definitions
// elágazás randomhoz

class Cell {
public:
    int x;
    int y;
    std::vector<bool> walls; // index 0: top |index 1: right| index 2: bottom| index 3: left
    bool visited;
    std::vector<Cell*> neighbors; // Pointers to neighboring Cell objects
    int matrix_val; // Renamed from matrix

    Cell(int x_val, int y_val) : x(x_val), y(y_val), visited(false) {
        walls = {true, true, true, true};
        // smallest way to the middle
        matrix_val = std::min({std::abs(7 - x_val) + std::abs(7 - y_val), // Corrected to use x_val, y_val
                               std::abs(8 - x_val) + std::abs(8 - y_val),
                               std::abs(8 - x_val) + std::abs(7 - y_val),
                               std::abs(7 - x_val) + std::abs(8 - y_val)});
    }

    // Default constructor for vector initialization or other cases.
    Cell() : x(0), y(0), visited(false) {
        walls = {true, true, true, true};
        // Default matrix_val for (0,0) or some indicator.
        // The actual value will be set when Cell(x,y) is assigned.
        matrix_val = std::min({std::abs(7 - 0) + std::abs(7 - 0), 
                               std::abs(8 - 0) + std::abs(8 - 0),
                               std::abs(8 - 0) + std::abs(7 - 0),
                               std::abs(7 - 0) + std::abs(8 - 0)}); // Calculated for (0,0)
    }
};

// Global helper functions
// smallest way to the middle
int calculate_matrix_value(int x, int y) {
    return std::min({std::abs(7 - x) + std::abs(7 - y),
                     std::abs(8 - x) + std::abs(8 - y),
                     std::abs(8 - x) + std::abs(7 - y),
                     std::abs(7 - x) + std::abs(8 - y)});
}

int matrix_5(int x, int y) {
    int first = calculate_matrix_value(x, y);
    int second = calculate_matrix_value(x, y + 1);
    int third = calculate_matrix_value(x, y - 1);
    int fourth = calculate_matrix_value(x - 1, y);
    int fifth = calculate_matrix_value(x + 1, y);
    int all_sum = first + second + third + fourth + fifth; // Renamed 'all'
    return all_sum;
}

class MouseCrashedError : public std::runtime_error {
public:
    MouseCrashedError() : std::runtime_error("Mouse crashed") {}
};


template<typename T>
void log(const T& message) {
    std::cerr << message << std::endl; // std::endl flushes
}
// Specialization for C-style strings if needed, but ostream usually handles it.
void log(const char* message) {
    std::cerr << message << std::endl;
}

// Algorithm functions
void checkWalls(Cell& cur, int irany) { // Pass Cell by reference
    if (!cur.visited) {
        log("-------Allitsuk be a current falait iranynak megfelelően-------------");
        log("jobb fal megnézése");
        if (!wallRight()) {
            if (irany == 8) { // E=8 H=2 B=4 J=6 billentyűzet
                cur.walls[1] = false;
                log("jobbra nincs");
            }
            if (irany == 6) {
                cur.walls[2] = false;
                log("lent nincs"); 
            }
            if (irany == 4) {
                cur.walls[0] = false;
                log("elol nincs");
            }
            if (irany == 2) {
                cur.walls[3] = false; 
                log("balra nincs"); 
            }
        }
    
        log("bal fal megnézése");
        if (!wallLeft()) {
            if (irany == 8) { // E=8 H=2 B=4 J=6 billentyűzet
                cur.walls[3] = false;
                log("balra nincs"); 
            }
            if (irany == 6) {
                cur.walls[0] = false; 
                log("elol nincs");
            }
            if (irany == 4) {
                cur.walls[2] = false;
                log("lent nincs");
            }
            if (irany == 2) {
                cur.walls[1] = false;
                log("jobbra nincs");  
            }
        }
                    
        log("upfal megnézése");
        if (!wallFront()) {
            if (irany == 8) { // E=8 H=2 B=4 J=6 billentyűzet
                cur.walls[0] = false;
                log("elol nincs");
            }
            if (irany == 6) {
                cur.walls[1] = false; 
                log("jobbra nincs");  
            }
            if (irany == 4) {
                cur.walls[3] = false;
                log("balra nincs"); 
            }
            if (irany == 2) {
                cur.walls[2] = false;  
                log("lent nincs");
            }
        }
    }
}

void addNeighbor(Cell& current, std::vector<std::vector<Cell>>& array_2d, std::vector<Cell*>& stack) {
    if (!current.visited) {
        log("-----------------Adjuk hozza a szomszedokat ha nincs fal-------");
        if (!current.walls[0]) { // ELŐTTE
            current.neighbors.push_back(&array_2d[current.x][(current.y) + 1]);
            log("fent");
        }
        if (!current.walls[1]) { // JOBBRA
            current.neighbors.push_back(&array_2d[(current.x) + 1][current.y]);
            log("jobbra");
        }
        if (!current.walls[2]) { // MÖGÖTTE
            current.neighbors.push_back(&array_2d[current.x][(current.y) - 1]);
            log("lent");
        }
        if (!current.walls[3]) { // BALRA
            current.neighbors.push_back(&array_2d[(current.x) - 1][current.y]);
            log("balra");
        }
        stack.push_back(&current);
        current.visited = true;
        log("Legyen visited a current");
    }
    // stack is modified by reference, no return needed
}
        
void getChoiceUnvisited(std::vector<Cell*>& unvisited, 
                          const Cell& current_cell_obj, // Changed name to avoid conflict
                          Cell*& next_chosen, 
                          bool& dead_end_flag,
                          const std::vector<std::vector<Cell>>& array_2d) { 
    log("Hany szomszed van:");
    log(current_cell_obj.neighbors.size());
    unvisited.clear(); 
    for (Cell* neighbor : current_cell_obj.neighbors) {
        if (!neighbor->visited) { 
            unvisited.push_back(neighbor);
        }
    }
    
    log("Unvisitednek a hossza:");
    log(unvisited.size());

    if (unvisited.empty()) { // zsak utca
        dead_end_flag = true;
        log("deadend");
        // next_chosen (Python's 'next') is not modified in this specific branch in Python
    } else if (unvisited.size() == 1) { // egy akkor csak erre
        next_chosen = unvisited[0];
    } else { // ha több mint egy(2 vagy 3)
        next_chosen = unvisited[0]; 
        for (size_t i = 0; i < unvisited.size(); ++i) { // Python: while i < len(unvisited)
            if (matrix_5(next_chosen->x, next_chosen->y) > matrix_5(unvisited[i]->x, unvisited[i]->y)) {
                next_chosen = unvisited[i];
            }
        }
    }
}

bool checkCurrentNeighborsHasUnv(const Cell& current) {
    for (const Cell* neighbor : current.neighbors) {
        if (!neighbor->visited) { 
            return true;
        }
    }
    return false;
}
        
void deadEndAndWallFrontTrue(int& E_H_B_J, std::vector<Cell*>& stack) { 
    if (wallFront() && wallLeft() && wallRight()) {
        turnLeft();
        turnLeft();
       
        if (E_H_B_J == 2) {
            E_H_B_J = 8;
        } else if (E_H_B_J == 8) {
            E_H_B_J = 2;
        } else if (E_H_B_J == 4) { 
            E_H_B_J = 6;
        } else if (E_H_B_J == 6) {
            E_H_B_J = 4;
        }
        
        if (!stack.empty()) {
            stack.pop_back(); // utolso helyet kivesszük. Python's pop() on empty list raises IndexError. C++ pop_back() on empty vector is UB.
        } else {
            log("CRITICAL: stack empty in deadEndAndWallFrontTrue. Python would crash.");
        }
    }
}

void go_to_next(const Cell& cur, Cell*& nex, int& irany, bool& dead_end_flag, std::vector<Cell*>& stack) {
    int yseged = cur.y - nex->y;
    int xseged = cur.x - nex->x; 
    
    if (xseged == 0 && yseged == 0) {
        dead_end_flag = true; 
        if (!stack.empty()) {
             nex = stack.back(); 
             stack.pop_back();   
        } else {
            log("CRITICAL: stack empty in goToNext when cur == nex. Python would crash.");
        }
        xseged = cur.x - nex->x;
        yseged = cur.y - nex->y;
        
        turnRight();
        if (irany == 8) {
            irany = 6;
        } else if (irany == 6) {
            irany = 2;
        } else if (irany == 4) { 
            irany = 8;
        } else if (irany == 2) { 
            irany = 4;
        }
    }
    
    if (xseged == 1) { // bal (nextnek jobb)
        nex->walls[1] = false;
        if (irany == 8) {
            turnLeft();
            irany = 4;
        }
        if (irany == 2) { 
            turnRight();
            irany = 4;
        }
    }
    if (xseged == -1) { // jobb (nextnek bal)
        nex->walls[3] = false;
        if (irany == 8) {
            turnRight();
            irany = 6;
        }
        if (irany == 2) { 
            turnLeft();
            log("miért balra he");
            irany = 6;
        }
    }
    if (yseged == 1) { // lent (nextnek felső)
        nex->walls[0] = false;
        if (irany == 6) {
            turnRight();
            irany = 2;
        }
        if (irany == 4) { 
            turnLeft();
            irany = 2; 
        }
    }
    if (yseged == -1) { // felső (nextnek alsó)
        nex->walls[2] = false;
        if (irany == 4) {
            turnRight();
            irany = 8;
        }
        if (irany == 6) { 
            turnLeft();
            irany = 8;
        }
    }
}        

int changeDirection180(int E_H_B_J) { 
    turnLeft();
    turnLeft();
    if (E_H_B_J == 8) {
        E_H_B_J = 2; 
    } else if (E_H_B_J == 2) {
        E_H_B_J = 8; 
    } else if (E_H_B_J == 4) {
        E_H_B_J = 6; 
    } else if (E_H_B_J == 6) {
        E_H_B_J = 4;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2500)); 
    return E_H_B_J;
}

void goBackToStart(int& E_H_B_J, bool& dead_end_flag, Cell*& next_cell, Cell*& current_cell, std::vector<Cell*>& stack) {
    for (int i = 1; i <= static_cast<int>(stack.size()) - 2; ++i) {
        Cell* target_next_in_path = stack[stack.size() - 1 - i]; 

        log(target_next_in_path->x);
        log(target_next_in_path->y);
        log("current:");
        log(current_cell->x);
        log(current_cell->y);
        log("next"); 
        log(target_next_in_path->x);
        log(target_next_in_path->y);
        
        Cell* nex_arg_for_goto = target_next_in_path; 
        go_to_next(*current_cell, nex_arg_for_goto, E_H_B_J, dead_end_flag, stack);
        next_cell = target_next_in_path; 
        go_to_next(*current_cell, next_cell, E_H_B_J, dead_end_flag, stack); 

        moveForward();     
        current_cell = next_cell; 
    }
}

void goBackToFinish(int& E_H_B_J, bool& dead_end_flag, Cell*& next_cell_param, Cell*& current_cell, 
                       std::vector<Cell*>& stack, 
                       int& flag_finish) {
    flag_finish = 0;
    for (size_t i = 0; i < stack.size(); ++i) {
        Cell* nex_for_this_iteration = next_cell_param; 
        if (i + 2 < stack.size()) {
            nex_for_this_iteration = stack[i + 2]; 
        }
        
        setColor(nex_for_this_iteration->x, nex_for_this_iteration->y, 'G');
        log("next");
        log(nex_for_this_iteration->x);
        log(nex_for_this_iteration->y);
        log("current");
        log(current_cell->x);
        log(current_cell->y);

        Cell* temp_nex_holder = nex_for_this_iteration; 
        go_to_next(*current_cell, temp_nex_holder, E_H_B_J, dead_end_flag, stack);
        next_cell_param = temp_nex_holder; 

        if ((current_cell->x == 7 && current_cell->y == 7) || 
            (current_cell->x == 7 && current_cell->y == 8) || 
            (current_cell->x == 8 && current_cell->y == 7) || 
            (current_cell->x == 8 && current_cell->y == 8)) {
            log("Finish");
            flag_finish = 1;
            break;
        }
        
        current_cell = next_cell_param; 
        moveForward();

        log("------------------------------------------------------------");
        log("Step ");
        log(i); 
        log("------------------------------------------------------------");
        setText(current_cell->x, current_cell->y, std::to_string(i)); 
    }
}  
          
int main() {
    try { 
        log("--------------------------------------Init------------------------------------------------");
        bool dead_end_flag = false; 
        int E_H_B_J = 8; 
        int how_far = 0;
        log("Running...");
        setColor(0, 0, 'G');
        setText(0, 0, "abc");
    
        log("--------------------------------------Feltölt------------------------------------------------");
        std::vector<std::vector<Cell>> array_2d(16, std::vector<Cell>(16));  
        for (int r = 0; r < 16; ++r) {
            for (int c = 0; c < 16; ++c) {
                array_2d[r][c] = Cell(r, c); 
            }
        }
        log("----------------------------------------------------------------------------------------");
        log("Finish beállítva,escurrent is:");
        
        Cell* current_ptr = &array_2d[0][0];
        std::vector<Cell*> stack_list; 
        stack_list.push_back(current_ptr); 
        Cell* next_ptr = current_ptr;
        
        while (true) { 
            log("koordinatam x:");
            log(current_ptr->x);
            log("koordinatam y:");
            log(current_ptr->y);
                
            if (!dead_end_flag) {
                checkWalls(*current_ptr, E_H_B_J); 
                addNeighbor(*current_ptr, array_2d, stack_list); 
                log("-----Ezeket a szomszedokat vizsgaljuk meg, hogy unvisited-e?-------");
                std::vector<Cell*> unvisited_list; 
                getChoiceUnvisited(unvisited_list, *current_ptr, next_ptr, dead_end_flag, array_2d); 
            }
            
            if (dead_end_flag) { 
                log("Hello ez itt zsák utca");
                deadEndAndWallFrontTrue(E_H_B_J, stack_list);  
                
                if (!stack_list.empty()) { 
                    next_ptr = stack_list.back();
                    stack_list.pop_back();
                } else {
                    log("CRITICAL: stack empty when trying to backtrack from dead_end. Python would crash.");
                }

                if (checkCurrentNeighborsHasUnv(*next_ptr)) { 
                    dead_end_flag = false;
                    stack_list.push_back(next_ptr); 
                }
            }
            
            go_to_next(*current_ptr, next_ptr, E_H_B_J, dead_end_flag, stack_list);

            if ((current_ptr->x == 7 && current_ptr->y == 7) || 
                (current_ptr->x == 7 && current_ptr->y == 8) || 
                (current_ptr->x == 8 && current_ptr->y == 7) || 
                (current_ptr->x == 8 && current_ptr->y == 8)) {
                log("Finish");
                break;
            }
            moveForward();
            current_ptr = next_ptr;

            log("koordinatam x:"); 
            log(current_ptr->x);
            log("koordinatam y:");
            log(current_ptr->y);
            log("koordinatam x:"); 
            log(next_ptr->x);
            log("koordinatam y:");
            log(next_ptr->y);
            
            how_far = how_far + 1; 
            setText(current_ptr->x, current_ptr->y, std::to_string(how_far));
            log("------------------------------------------------------------");
            log("Step ");
            log(how_far);
            log("------------------------------------------------------------");
        }
            
        log("Go back to start");
        E_H_B_J = changeDirection180(E_H_B_J);
        goBackToStart(E_H_B_J, dead_end_flag, next_ptr, current_ptr, stack_list);
        
        int flag_finish = 0;
        log("Going back using the shortest path");
        E_H_B_J = changeDirection180(E_H_B_J);
        goBackToFinish(E_H_B_J, dead_end_flag, next_ptr, current_ptr, stack_list, flag_finish);
        if (flag_finish == 1) {
            log(":)");
        }
    } catch (const MouseCrashedError& e) {
        log("MouseCrashedError caught!");
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1; 
    } catch (const std::exception& e) {
        log("Standard exception caught!");
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1; 
    } catch (...) {
        log("Unknown exception caught!");
        std::cerr << "Unknown exception occurred" << std::endl;
        return 1; 
    }
        
    return 0; 
}
