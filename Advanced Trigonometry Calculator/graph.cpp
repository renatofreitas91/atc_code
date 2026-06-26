#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <io.h>

#ifdef _WIN32
#include <windows.h>

static bool hasInteractiveGraphConsole() {
    DWORD mode = 0;
    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    if (input == INVALID_HANDLE_VALUE || output == INVALID_HANDLE_VALUE) {
        return false;
    }
    if (GetFileType(input) != FILE_TYPE_CHAR || GetFileType(output) != FILE_TYPE_CHAR) {
        return false;
    }
    return _isatty(_fileno(stdin)) && _isatty(_fileno(stdout)) &&
        GetConsoleMode(input, &mode) && GetConsoleMode(output, &mode);
}

#endif
template <typename T>
void designGraph(char* functionF) {
    FILE* open;
    int numberCols = 0;
#ifdef _WIN32
    bool graphInteractiveConsole = hasInteractiveGraphConsole();
    const char* graphNavigationTest = getenv("ATC_GRAPH_NAVIGATION_TEST");
#endif
    char* toOpen = getDynamicCharArray("", "toOpen");
    char* setting = getDynamicCharArray("", "setting");

    if (!graphInteractiveConsole && graphNavigationTest == nullptr) {
        printf("\n==> Graph non-interactive mode <==\n");
        printf("Function: %s\n", functionF);
        printf("Current settings: | Xmin: _10 | Xmax: 10 | Xscale: 1 | Ymin: auto | Ymax: auto | Yscale: auto |\n");
        _delete(toOpen, "toOpen"); toOpen = nullptr;
        _delete(setting, "setting"); setting = nullptr;
        return;
    }

    // Safer bounded formatting replacing raw sprintf
    snprintf(toOpen, DIM, "%s\\dimensions.txt", atcPath);

    if (fopen(toOpen, "r") == NULL) {
#ifdef _WIN32
        if (graphInteractiveConsole) {
            system("MODE con cols=160 lines=300");
        }
#endif
        numberCols = 160;
    }
    else {
        open = fopen(toOpen, "r");
        fgets(setting, 40, open);
        fclose(open);
        if (isContained("MODE con cols=", setting)) {
            int k = strEnd, l = 0;
            char* number = getDynamicCharArray("", "number");
            while (verifyNumber(setting[k])) {
                number[l] = setting[k];
                k++; l++;
            }
            number[l] = '\0';
            numberCols = atoi(number);
            _delete(number, "number");
            number = nullptr;
        }
    }

    T x_lower = -77777, x_scaleF = -77777, x_higher = -77777;
    if (isContained(";", functionF)) {
        char* limitInfo = getDynamicCharArray("", "limitInfo");
        int hj = strStart + 1;
        int hi = 0;
        while (hj < abs((int)strlen(functionF))) {
            limitInfo[hi] = functionF[hj];
            hj++; hi++;
        }
        limitInfo[hi] = '\0';

        int countBars = 0;
        int numberBars = countOccurrences("\\", limitInfo);
        if (numberBars > 0 && numberBars < 3) {
            int vb = 0, va = 0;
            char* value = getDynamicCharArray("", "value");
            for (vb = 0; vb < abs((int)strlen(limitInfo)); vb++) {
                if (limitInfo[vb] != '\\') {
                    value[va] = limitInfo[vb];
                    va++;
                }
                else {
                    value[va] = '\0';
                    countBars++;
                    if (countBars == 1) {
                        x_lower = solveMath<T>(value);
                    }
                    if (countBars == 2) {
                        x_higher = solveMath<T>(value);
                    }
                    va = 0;
                }
            }
            value[va] = '\0';
            countBars++;
            if (countBars == 3) {
                x_scaleF = solveMath<T>(value);
                while (x_scaleF < (x_higher - x_lower) / 120) {
                    printf("Xscale? (minimum: %s)\n", convert2Exponential(abs(x_higher - x_lower) / 120));
                    x_scaleF = getValue<T>();
                }
            }
            _delete(value, "value");
            value = nullptr;
        }
        else {
            puts("\nError: The number of parameter must be 2 or 3. The first two parameters are mandatory, i.e. the lower value for x and the higher value for x. The third parameter is the scale of x.");
        }
        replace(";", "", functionF);
        snprintf(functionF, DIM, "%s", expressionF);
        replace(limitInfo, "", functionF);
        snprintf(functionF, DIM, "%s", expressionF);
        _delete(limitInfo, "limitInfo");
        limitInfo = nullptr;
    }

    char* function = getDynamicCharArray("", "function");
    if (isContained("x", functionF)) {
        replace("x", "res", functionF);
        snprintf(function, DIM, "%s", expressionF);
    }

    int t = 0, w = 0, p = 0;
    char** functions;
    functions = new char* [DIMTWOD];

    for (int i = 0; i < DIMTWOD; ++i) {
        functions[i] = getDynamicCharArray("", "functions[i]");
    }

    for (t = 0; t < abs((int)strlen(functionF)); t++) {
        if (functionF[t] != '\\') {
            functions[w][p] = functionF[t];
            p++;
        }
        else {
            functions[w][p] = '\0';
            p = 0;
            w++;
        }
    }

    FILE* graph = NULL;
    T Xmin, Xmax, Xscale, Ymin, Ymax, Yscale, auto_y_axis, auto_x_axis;
    snprintf(toOpen, DIM, "%s\\graph.txt", atcPath);
    graph = fopen(toOpen, "r");
    if (x_lower != -77777 && x_higher != -77777 && graph == NULL) {
        Xmin = x_lower;
        Xmax = x_higher;
        Xscale = (x_scaleF != -77777) ? x_scaleF : 1;
        Ymin = -1E-20; Ymax = 1E-20; Yscale = 1E-21;
        auto_y_axis = 1; auto_x_axis = 1;
    }
    else {
        if (graph == NULL) {
            Xmin = -10; Xmax = 10; Xscale = 1;
            Ymin = -1E-20; Ymax = 1E-20; Yscale = 1E-21;
            auto_y_axis = 1; auto_x_axis = 1;
        }
        else {
            char* data = getDynamicCharArray("", "data");
            int i = 0;
            // Prevent dynamic heap overflow during raw character streaming
            for (i = 0; i < DIM - 1 && (data[i] = fgetc(graph)) != EOF; i++);
            data[i] = '\0';
            fclose(graph);

            i = 0; int j = 0;
            char* value = getDynamicCharArray("", "value"); // Fixed dynamic memory initialization state visibility

            while (data[i] != '\n' && i < abs((int)strlen(data))) { value[j] = data[i]; i++; j++; }
            value[j] = '\0'; Xmin = (x_lower == -77777) ? solveMath<T>(value) : x_lower;

            i++; j = 0;
            while (data[i] != '\n' && i < abs((int)strlen(data))) { value[j] = data[i]; i++; j++; }
            value[j] = '\0'; Xmax = (x_higher == -77777) ? solveMath<T>(value) : x_higher;

            i++; j = 0;
            while (data[i] != '\n' && i < abs((int)strlen(data))) { value[j] = data[i]; i++; j++; }
            value[j] = '\0'; Xscale = (x_scaleF == -77777) ? solveMath<T>(value) : x_scaleF;

            i++; j = 0;
            while (data[i] != '\n' && i < abs((int)strlen(data))) { value[j] = data[i]; i++; j++; }
            value[j] = '\0'; Ymin = solveMath<T>(value);

            i++; j = 0;
            while (data[i] != '\n' && i < abs((int)strlen(data))) { value[j] = data[i]; i++; j++; }
            value[j] = '\0'; Ymax = solveMath<T>(value);

            i++; j = 0;
            while (data[i] != '\n' && i < abs((int)strlen(data))) { value[j] = data[i]; i++; j++; }
            value[j] = '\0'; Yscale = solveMath<T>(value);

            i++; j = 0;
            while (data[i] != '\n' && i < abs((int)strlen(data))) { value[j] = data[i]; i++; j++; }
            value[j] = '\0'; auto_y_axis = solveMath<T>(value);

            i++; j = 0;
            while (data[i] != '\n' && i < abs((int)strlen(data))) { value[j] = data[i]; i++; j++; }
            value[j] = '\0'; auto_x_axis = solveMath<T>(value);

            _delete(data, "data"); data = nullptr;
            _delete(value, "value"); value = nullptr;
        }
    }

    T** yValuesAll;
    yValuesAll = new T* [DIMTWOD];
    for (int i = 0; i < DIMTWOD; ++i) {
        yValuesAll[i] = getDynamicArray<T>(DIMDOUBLE); // Must accommodate 121 cells safely
    }

    T xDim = Xmax - Xmin;
    T valuePerxDim = 120 / xDim;
    T yDim = Ymax - Ymin;
    T valuePeryDim = 60 / yDim;
    T valueXPerXscale = Xscale * valuePerxDim;
    T valueYPerYscale = Yscale * valuePeryDim;
    T x_scale = (Xscale / (xDim / 120)), y_scale = ((Yscale) / (yDim / 60));
    solverRunning = true;
    solving = false;
    int i = 0, j = 0;
    int y = (int)abs(Ymax);
    y = (int)(y / ((T)yDim / 60));
    int x = (int)abs(Xmin);
    x = (int)(x / ((T)xDim / 120));
    int commas = 1;
    if (isContained("\\", function)) {
        for (j = 0; j < abs((int)strlen(function)); j++) {
            if (function[j] == '\\') {
                commas++;
            }
        }
    }
    char* specFunction = getDynamicCharArray("", "specFunction");
    snprintf(specFunction, DIM, "%s", function);
    int r = 0, e = 0, count = 0;
    char* info = getDynamicCharArray("", "info");

    if (auto_x_axis == 1) {
        char* function_list = getDynamicCharArray("cos,acos,sin,asin,tan,atan,sec,asec,cosec,acosec,cotan,acotan,log,ln,rest,quotient,sqrt,cbrt,afact,cosh,acosh,sinh,asinh,tanh,atanh,sech,asech,cosech,acosech,cotanh,acotanh,sinc,gerror,gerrorinv,gerrorc,gerrorcinv,qfunc,qfuncinv,cbrt,sqrt,atc,solver,det,abs,strlen,i,countoccurrences,iscontained,iscontainedbyindex,iscontainedvariable,isequal,isvariable,istowrite,for,calc,max,min,linsnum,colsnum,getlins,getcols,avg,", "function_list");
        char* func = getDynamicCharArray("", "func");
        bool hasFunction = false;
        for (int f = 0; f < abs((int)strlen(function_list)); f++) {
            int g = 0;
            while (f < abs((int)strlen(function_list)) && function_list[f] != ',') {
                func[g] = function_list[f];
                g++; f++;
            }
            func[g] = '\0';
            if (isContained(func, functionF)) {
                hasFunction = true;
            }
        }
        if (!hasFunction) {
            manageExpression<double>(functionF, 0.0, 0.0, 1);
            snprintf(functionF, DIM, "%s", expressionF);
            replaceTimes = 0;
            if (isContained("(x)", functionF)) {
                replace("(x)", "x", functionF);
                snprintf(functionF, DIM, "%s", expressionF);
            }
            simplifyExpression(functionF);
            sprintf(roots, "");
            snprintf(functionF, DIM, "(%s)", expressionF);
            equationSolver<T>(functionF);
        }
        Xscale = -77777;
        if (abs((int)strlen(roots)) > 0 && !hasFunction) {
            if (isContained("1", roots) || isContained("2", roots) || isContained("3", roots) || isContained("4", roots) || isContained("5", roots) || isContained("6", roots) || isContained("7", roots) || isContained("8", roots) || isContained("9", roots) || isContained("0", roots)) {
                char* Roots = getDynamicCharArray("", "Roots");
                snprintf(Roots, DIM, "%s", roots);
                maximum(Roots);
                if (precisionValueTo<T>(resultR) != 0 && precisionValueTo<T>(resultI) != -DBL_MAX && abs(precisionValueTo<T>(resultI)) < 0.01) {
                    x_higher = precisionValueTo<T>(resultR);
                    snprintf(Roots, DIM, "%s", roots);
                    minimum(Roots);
                    if (abs(precisionValueTo<T>(resultI)) < 0.01) {
                        x_lower = precisionValueTo<T>(resultR);
                        x_lower = x_lower - 5;
                        x_higher = x_higher + 5;
                        Xmin = x_lower;
                        Xmax = x_higher;
                        Xscale = (x_higher - x_lower) / 20;
                    }
                }
                _delete(Roots, "Roots");
                Roots = nullptr;
            }
        }
        _delete(function_list, "function_list"); function_list = nullptr;
        _delete(func, "func"); func = nullptr;
    }

    if (auto_y_axis == 1) {
        do {
            e = 0;
            while (function[r] != '\\' && r < abs((int)strlen(function))) {
                specFunction[e] = function[r];
                r++; e++;
            }
            specFunction[e] = '\0';
            r++;
            T start = Xmin;
            int f = 0;
            T yValues[121] = { 0,0 };
            T newYmax = 1E-20, newYmin = -1E-20;
            while (f < 121) {
                xValuesR = start; xValuesI = 0;
                solveMath<T>(specFunction);
                yValues[f] = precisionValueTo<T>(resultR);
                yValuesAll[count][f] = precisionValueTo<T>(resultR);
                if (yValues[f] < newYmin && yValues[f] > -1E14) {
                    newYmin = yValues[f];
                }
                if (yValues[f] > newYmax && yValues[f] < 1E14) {
                    newYmax = yValues[f];
                }
                resultR = 0; resultI = 0;
                start = start + (T)xDim / 120;
                f++;
            }
            if (newYmin < Ymin || newYmax > Ymax) {
                if (abs(newYmin) > abs(newYmax)) {
                    newYmax = abs(newYmin);
                }
                else {
                    newYmin = abs(newYmax) * -1;
                }
                Ymax = ceil(newYmax);
                Ymin = floor(newYmin);
                Yscale = abs(Ymax - Ymin) / 20;
                xDim = abs(Xmax - Xmin);
                valuePerxDim = 120 / xDim;
                yDim = abs(Ymax - Ymin);
                valuePeryDim = 60 / yDim;
                valueXPerXscale = Xscale * valuePerxDim;
                valueYPerYscale = Yscale * valuePeryDim;
                i = 0; j = 0;
                y = (int)abs(Ymax);
                y = (int)(y / ((T)yDim / 60));
                x = (int)abs(Xmin);
                x = (int)(x / ((T)xDim / 120));
            }
            x_scale = (Xscale / (xDim / 120)); y_scale = ((Yscale) / (yDim / 60));
            commas--;
            count++;
        } while (commas > 0);
    }

    commas = 1;
    if (isContained("\\", function)) {
        for (j = 0; j < abs((int)strlen(function)); j++) {
            if (function[j] == '\\') {
                commas++;
            }
        }
    }

    char** Graph;
    Graph = new char* [DIMTWOD];
    for (int i = 0; i < 60; ++i) {
        Graph[i] = getDynamicCharArray("", "Graph[i]");
    }

    i = 0; j = 0;
    for (i = 0; i < 60; i++) {
        for (j = 0; j < 120; j++) {
            Graph[i][j] = ' ';
        }
    }
    for (i = 0; i < 60; i++) {
        Graph[y][i] = '_';
        if (re<T>(i, x_scale) == 0) {
            Graph[y + 1][i] = (char)179;
        }
        Graph[i][x] = (char)179;
        if (re<T>(i, y_scale) == 0) {
            Graph[i][x + 1] = '_';
        }
    }
    for (i = 60; i < 120; i++) {
        Graph[y][i] = '_';
        if (re<T>(i, x_scale) == 0) {
            Graph[y + 1][i] = (char)179;
        }
    }

    snprintf(specFunction, DIM, "%s", function);
    r = 0; e = 0; count = 0;
    char* symbols = getDynamicCharArray("XYZOABCDEFGHIJKLMNOPQRSTUVW/*-+_xo", "symbols");

    do {
        e = 0;
        while (function[r] != '\\' && r < abs((int)strlen(function))) {
            specFunction[e] = function[r];
            r++; e++;
        }
        specFunction[e] = '\0';
        r++;
        T start = Xmin;
        int f = 0;
        T yValues[121] = { 0,0 };

        // Critical Alignment Fix: Evaluate all 121 items cleanly
        while (f < 121) {
            xValuesR = start; xValuesI = 0;
            solveMath<T>(specFunction);
            yValues[f] = precisionValueTo<T>(resultR);
            yValuesAll[count][f] = precisionValueTo<T>(resultR);
            resultR = 0; resultI = 0;
            start = start + (T)xDim / 120;
            f++;
        }

        f = 0;
        int saveK = 0, saveKK = 0;
        while (f < 120) {
            T yValue = yValues[f];
            int k = 0;
            if (yValue > Ymin && yValue < Ymax) {
                T l = Ymax, l_2 = 0;
                for (k = 0; k < 60; k++) {
                    l = Ymax - k * (T)yDim / 60;
                    l_2 = Ymax - (k + 2) * (T)yDim / 60;
                    if (yValue < l && yValue > l_2) {
                        break;
                    }
                }
                if (saveK != 0) {
                    if (saveK > k + 1) {
                        while (saveK > k + 1) {
                            if (saveK != saveKK) {
                                Graph[saveK][f - 1] = '|';
                            }
                            saveK--;
                        }
                    }
                    else {
                        while (saveK < k + 1) {
                            if (saveK != saveKK) {
                                Graph[saveK][f - 1] = '|';
                            }
                            saveK++;
                        }
                    }
                }
                Graph[k + 1][f] = symbols[count];
                saveK = k + 1;
                if (saveK == saveKK) {
                    Graph[k + 1][f] = '-';
                    Graph[k + 1][f - 1] = '-';
                }
                saveKK = k + 1;
            }
            f++;
        }
        if (isContained("res", specFunction)) {
            replace("res", "x", specFunction);
            snprintf(specFunction, DIM, "%s", expressionF);
        }
        if (count < commas) {
            snprintf(info, DIM, "%s%s -> %c %c", info, specFunction, symbols[count], 179);
        }
        else {
            snprintf(info, DIM, "%s%s -> %c", info, specFunction, symbols[count]);
        }
        count++;
        commas--;
    } while (commas > 0);

    if (graphNavigationTest == nullptr) {
        puts("Info: You can navigate with the \"Left\" and \"Right\" arrows. To exit press the \"Escape\" key; Action: Press \"Enter\" to view the graph.");
        char* pause = getDynamicCharArray("", "pause");
        gets_s(pause, DIM);

        for (j = 0; j < 121; j++) {
            printf("_");
        }
        printf("\n");
        for (i = 0; i < 60; i++) {
            printf("%c", 179);
            for (j = 0; j < 120; j++) {
                printf("%c", Graph[i][j]);
            }
            printf("%c", 179);
            printf("\n");
        }
        printf("%c", 179);
        for (j = 0; j < 120; j++) {
            printf("_");
        }
        printf("%c", 179);
        printf("\n");
        printf(" Current settings: %c Xmin: %G %c Xmax: %G %c Xscale: %G %c Ymin: %G %c Ymax: %G %c Yscale: %G %c", 179, Xmin, 179, Xmax, 179, Xscale, 179, Ymin, 179, Ymax, 179, Yscale, 179);
        _delete(pause, "pause"); pause = nullptr;
    }

    solverRunning = false;
    solving = true;

#ifdef _WIN32
    if (!graphInteractiveConsole && graphNavigationTest != nullptr) {
        int index = 0;
        for (int keyIndex = 0; graphNavigationTest[keyIndex] != '\0'; keyIndex++) {
            if ((graphNavigationTest[keyIndex] == 'L' || graphNavigationTest[keyIndex] == 'l') && index > 0) {
                index--;
            }
            if ((graphNavigationTest[keyIndex] == 'R' || graphNavigationTest[keyIndex] == 'r') && index < 120) {
                index++;
            }
        }
        printf("\n==> Graph navigation test <==\n");
        printf("Index: %d\n", index);
        printf("x = %f\n", precisionDisplayDouble(Xmin + index * (T)xDim / 120));
        for (t = 0; t <= w; t++) {
            printf("%s [%c]: %f\n", functions[t], symbols[t], precisionDisplayDouble(yValuesAll[t][index]));
        }
    }
#endif

    // Interactive Loop isolated cleanly for Windows CLI. 
    // In WebAssembly environment, it gracefully skips the unsupported polling engine.
#ifdef _WIN32
    if (graphInteractiveConsole) {
        int option = 1;
        int index = 0;
        int rf = 0;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        COORD cursorPosition = GetConsoleCursorPosition(hConsole);

        GoToXY(1, cursorPosition.Y - 1);
        ShowConsoleCursor(FALSE);

        int BarsLenght = 0, DataLength = 0, saveBarsLenght = 0, saveDataLength = 0;
        DWORD cNumRead;
        INPUT_RECORD irInBuf[128];

        FlushConsoleInputBuffer(hInput);

        while (option == 1) {
            GetNumberOfConsoleInputEvents(hInput, &cNumRead);
            if (cNumRead > 0) {
                ReadConsoleInput(hInput, irInBuf, 128, &cNumRead);
                for (DWORD idx = 0; idx < cNumRead; idx++) {
                    if (irInBuf[idx].EventType == KEY_EVENT && irInBuf[idx].Event.KeyEvent.bKeyDown) {
                        WORD wKeyCode = irInBuf[idx].Event.KeyEvent.wVirtualKeyCode;
                        bool updateNeeded = false;

                        if (wKeyCode == VK_LEFT) {
                            if (index > 0) {
                                index--;
                                updateNeeded = true;
                            }
                        }
                        else if (wKeyCode == VK_RIGHT) {
                            if (index < 120) { // Safely bound to max accessible calculated index (120)
                                index++;
                                updateNeeded = true;
                            }
                        }
                        else if (wKeyCode == VK_ESCAPE) {
                            ShowConsoleCursor(TRUE);
                            GoToXY(cursorPosition.X, cursorPosition.Y);
                            option = 0;
                            break;
                        }

                        if (updateNeeded) {
                            t = 0;
                            char* data = getDynamicCharArray("", "data");
                            for (t = 0; t <= w; t++) {
                                snprintf(data + strlen(data), DIM - strlen(data), "%s [%c]: %f  ", functions[t], symbols[t], yValuesAll[t][index]);
                            }
                            DataLength = abs((int)strlen(data));

                            char* bars = getDynamicCharArray("", "bars");
                            rf = 0;
                            while (rf < index && rf < numberCols - 2) {
                                snprintf(bars + strlen(bars), DIM - strlen(bars), "%c", 178);
                                rf++;
                            }
                            snprintf(bars + strlen(bars), DIM - strlen(bars), "x = %f ", Xmin + index * (T)xDim / 120);
                            rf = abs((int)strlen(bars));
                            while (rf < numberCols && rf < 120) {
                                snprintf(bars + strlen(bars), DIM - strlen(bars), "%c", 177);
                                rf++;
                            }
                            BarsLenght = abs((int)strlen(bars));

                            if (BarsLenght < saveBarsLenght) {
                                GoToXY(BarsLenght + 1, cursorPosition.Y - 29);
                                for (rf = BarsLenght; rf < saveBarsLenght; rf++) printf(" ");
                            }
                            GoToXY(1, cursorPosition.Y - 29);
                            printf("%s", bars);

                            if (DataLength < saveDataLength) {
                                GoToXY(DataLength + 1, cursorPosition.Y - 28);
                                for (rf = DataLength; rf < saveDataLength; rf++) printf(" ");
                            }
                            GoToXY(1, cursorPosition.Y - 28);
                            printf("%s", data);

                            saveBarsLenght = BarsLenght;
                            saveDataLength = DataLength;

                            _delete(data, "data"); data = nullptr;
                            _delete(bars, "bars"); bars = nullptr;
                        }
                    }
                }
            }
            Sleep(20);
        }
    }
#endif

    int option_table = -1;
    while (option_table != 1 && option_table != 0) {
        I_O = true;
        puts("\nDo you want to see the graph data in table form? (Yes -> 1 \\ No -> 0)");
        option_table = (int)getValue<T>();
    }

    if (option_table == 1) {
        char* valueToText = getDynamicCharArray("", "valueToText");
        int k = 0, l = 0;
        puts(" ");
        printf("%cx", 179);
        int g = 0;
        while (g < 11) { printf(" "); g++; }
        k = 0;
        while (k < count) {
            printf("%c%c", 179, symbols[k]);
            int g = 0;
            while (g < 11) { printf(" "); g++; }
            k++;
        }
        printf("\n");
        T start = Xmin;
        while (l < 121) {
            k = 0;
            printf("%c%s", 179, convert2Exponential(start));
            snprintf(valueToText, DIM, "%c%s", 179, convert2Exponential(start));
            g = (int)abs((int)strlen(valueToText));
            while (g < 13) { printf(" "); g++; }
            while (k < count) {
                printf("%c%s", 179, convert2Exponential(yValuesAll[k][l]));
                snprintf(valueToText, DIM, "%c%s", 179, convert2Exponential(yValuesAll[k][l]));
                g = (int)abs((int)strlen(valueToText));
                while (g < 13) { printf(" "); g++; }
                k++;
            }
            printf("\n");
            start = start + (T)xDim / 120;
            l++;
        }
        _delete(valueToText, "valueToText");
        valueToText = nullptr;
    }

    // Dynamic clean up memory tracking routines
    _Delete(functions, DIMTWOD, 200, "functions[i]");
    _Delete(yValuesAll, DIMTWOD, 121, "yValuesAlls[i]");
    _Delete(Graph, 60, 120, "Graph[i]");

    Graph = nullptr;
    _delete(toOpen, "toOpen"); toOpen = nullptr;
    _delete(setting, "setting"); setting = nullptr;
    _delete(function, "function"); function = nullptr;
    _delete(specFunction, "specFunction"); specFunction = nullptr;
    _delete(info, "info"); info = nullptr;
    _delete(symbols, "symbols"); symbols = nullptr;
}



void GoToXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, coord);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

template void designGraph<double>(char*);
