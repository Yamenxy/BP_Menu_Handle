#include <iostream>
#include <conio.h>
#include <vector>
#include <chrono>
#include <thread>
#include "tiny-json.h"

#define KEY_UP (72)
#define KEY_down (80)
#define KEY_ESC (27)

using namespace std;

struct MenuItem {
    string title;
    int ser_id;
};

void tim() {
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << ctime(&end_time);
}

void displayMenuItems(const vector<MenuItem>& menuItems, int page ,int PageItemsCount) {
    int i = 0;
    cout << "press ESC to exit\t\t\t\t Main Menu\t\t\t\t\t";
    tim();
    cout << "\t\t\t\t\t\t   Page " << page << "\n";
    for (const auto& item : menuItems) {
        i++;
        cout << i << "-" << item.title << endl;
        if (i == PageItemsCount) {
            i = 0;
        }
    }
}

void disp(int sec) {
    using namespace std::this_thread;
    using namespace std::chrono;
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(sec));
}

int main(void) {
    int page = 1;
    char key;

    char menuItems[] = "\n"
                       "{\n"
                       "\"menus\": {\n"
                       "\t\"size\": 8,\n"
                       "\t\"PageItemsCount\": 6,\n"
                       "\t\"display\": [\n"
                       "\t\t{ \"title\": \"Menu Item 1\", \"ser_id\": 900},\n"
                       "\t\t{ \"title\": \"Menu Item 2\", \"ser_id\": 901},\n"
                       "\t\t{ \"title\": \"Menu Item 3\", \"ser_id\": 902},\n"
                       "\t\t{ \"title\": \"Menu Item 4\", \"ser_id\": 903},\n"
                       "\t\t{ \"title\": \"Menu Item 5\", \"ser_id\": 904},\n"
                       "\t\t{ \"title\": \"Menu Item 6\", \"ser_id\": 905},\n"
                       "\t\t{ \"title\": \"Menu Item 7\", \"ser_id\": 906},\n"
                       "\t\t{ \"title\": \"Menu Item 8\", \"ser_id\": 907},\n"
                       "\t] }\t\n"
                       "}";

    json_t mem[32];
    json_t const* json = json_create(menuItems, mem, sizeof mem / sizeof *mem);
    if (!json) {
        puts("Error json create.");
        return EXIT_FAILURE;
    }

    json_t const* menus = json_getProperty(json, "menus");
    if (!menus)
    {
        puts("Error, the 'menus' object is not found.");
        return EXIT_FAILURE;
    }


    json_t const* size = json_getProperty(menus, "size");
    if (!size)
    {
        puts("Error, the size is not found.");
        return EXIT_FAILURE;
    }

    int sizeval = json_getInteger(size);
    cout<<sizeval;

    json_t const* PageItemsCount = json_getProperty(menus, "PageItemsCount");
    if (!PageItemsCount || JSON_INTEGER != json_getType(PageItemsCount))
    {
        puts("Error, the 'PageItemsCount' property is not found or not of integer type.");
        return EXIT_FAILURE;
    }

    int itemsPerPage = json_getInteger(PageItemsCount);
    cout << itemsPerPage << endl;

    int totalPages = (sizeval + itemsPerPage - 1) / itemsPerPage;
    cout << totalPages << endl;
    vector<MenuItem> menuItemsVector;

    json_t const* display = json_getProperty(menus, "display");
    if (!display)
    {
        puts("Error");
        return EXIT_FAILURE;
    }

    for (json_t const* item = json_getChild(display); item != 0; item = json_getSibling(item))
    {
        if (JSON_OBJ == json_getType(item))
        {
            char const* itemTitle = json_getPropertyValue(item, "title");
            int ser_id = json_getInteger(json_getProperty(item, "ser_id"));
            menuItemsVector.push_back({itemTitle, ser_id});
        }
    }

    int currentPage = 0;
    bool flag=true;
    do {
        if(flag)
        {
            system("cls");

            int startIndex = currentPage * itemsPerPage;
            int endIndex = min(startIndex + itemsPerPage, static_cast<int>(menuItemsVector.size()));
            vector<MenuItem> currentPageItems(menuItemsVector.begin() + startIndex, menuItemsVector.begin() + endIndex);

            displayMenuItems(currentPageItems, page,itemsPerPage);
            flag=false;
        }

        if(_kbhit())
        {
            key = _getch();
            if (key == KEY_UP && currentPage > 0)
            {
                if(page==1){
                    flag=false;
                }
                else{
                currentPage--;
                page--;
                cout << "\a";
                flag=true;
                }
            }
            else if (key == KEY_down && currentPage < totalPages - 1)
            {
                if(page == totalPages )
                {
                    flag=false;
                }
                else
                {
                    currentPage++;
                    page++;
                    cout << "\a";
                    flag=true;
                }
            }
            else if (key >= '1' && key <= 'itemsPerPage')
            {
                int index = (currentPage * itemsPerPage) + (key - '1');
                if (index >= 0 && index < menuItemsVector.size())
                {
                    int ser_id = menuItemsVector[index].ser_id;
                    cout << "\aSelected item ser_id: " << ser_id << endl;
                    disp(1.5);
                }
                flag=true;
            }

        }
    } while (key != KEY_ESC);

    cout << "\a";
    system("cls");
    cout << "Program ended in: ";
    tim();


    return 0;
}
