#pragma once
#define _WINSOCKAPI_ // Prevent inclusion of winsock.h
// Windows-specific headers
#include "targetver.h"    // Include project specific version info
#define NOMINMAX
#include <windows.h>
#include <algorithm>

// Standard C++ libraries
#include <cstdio>         // C Standard Input and Output
#include <cstdlib>       // C Standard Library
#include <cstring>       // C String handling
#include <cmath>         // C Math library
#include <ctime>         // C Time handling
#include <fstream>       // C++ File stream
#include <string>        // C++ String handling
#include <vector>        // Dynamic arrays
#include <iostream>      // Standard I/O stream
#include <sstream>       // String stream formatting
#include <iomanip>       // Decimal precision formatting
#include <limits>        // Numeric limits
#include <complex>       // Complex numeric solver helpers
#include <conio.h>       // Console I/O
#include <io.h>          // Console redirection checks
#include <tchar.h>       // Generic text mapping
#include <shellapi.h>    // Shell API
#include <tlhelp32.h>    // Tool Help Library
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>



// Boost libraries
#include <boost/math/special_functions/erf.hpp>
#include <boost/math/constants/constants.hpp>



#include "resource.h"
#include "dirent.h"

// É obrigatório incluir os cabeçalhos da Boost que definem o cpp_dec_float and number
#include <boost/multiprecision/cpp_dec_float.hpp>

// Definição do tipo para alta precisão (50 dígitos decimais)
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<50>> mp_float;

#include <boost/variant.hpp>
using PrecisionDoublePointer = boost::variant<double**, mp_float**>;

// Usamos a variante da Boost em vez da std
using PrecisionPointer = boost::variant<double*, mp_float*>;
using PrecisionValue = boost::variant<double, mp_float>;

#include "calc.h"
#include <algorithm>
#include "atc_functions.h"
#include <unordered_map>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#ifndef DISABLE_NEWLINE_AUTO_RETURN
#define DISABLE_NEWLINE_AUTO_RETURN 0x0008
#endif

#ifndef ENABLE_VIRTUAL_TERMINAL_INPUT
#define ENABLE_VIRTUAL_TERMINAL_INPUT 0x0200
#endif
// Adiciona constexpr aqui
extern float memFactor;


void setMemFactor1(float memFactor);



extern int DIM;
extern int dime;
extern int SHORTDIM;
extern int LONGDIM;
extern int DIMTWOD;
extern int DIMDOUBLE;


// Link the necessary libraries
#pragma comment(lib,"Wininet.lib")    // Link Wininet library
extern char** splitResult;



struct DynamicAllocationData {
    std::string name;
    std::string data;
    std::string address;
    int sizeAllocated = 0;
};

struct DynamicAllocation {
    std::vector<DynamicAllocationData> allocations;

    size_t getCount() const {
        return allocations.size();
    }

    int getPosition(const std::string& name) const {
        for (size_t position = 0; position < allocations.size(); ++position) {
            if (allocations[position].name == name) {
                return static_cast<int>(position);
            }
        }
        return -1;
    }
    std::string getAddressAsString(const void* ptr) const {
        std::ostringstream oss;
        oss << ptr; // formata como "0x..."
        return oss.str();
    }


    bool pointerExists(const void* ptr) const {
        if (!ptr) return false;
        std::string addr = getAddressAsString(ptr);
        return getSizeByAddress(addr) > 0;
    }
    DynamicAllocationData getObject(const std::string& name) const {
        int position = getPosition(name);
        if (position != -1) {
            return allocations[position];
        }
        return DynamicAllocationData{};
    }

    bool objectExist(const std::string& name) const {
        return getPosition(name) != -1;
    }

    DynamicAllocationData getObject(int position) const {
        if (position >= 0 && static_cast<size_t>(position) < allocations.size()) {
            return allocations[position];
        }
        return DynamicAllocationData{};
    }

    bool replaceObject(const DynamicAllocationData& object, int position) {
        if (position >= 0 && static_cast<size_t>(position) < allocations.size()) {
            allocations[position] = object;
            return true;
        }
        return false;
    }

    bool tryReplaceObject(const DynamicAllocationData& object) {
        int position = getPosition(object.name);
        if (position != -1) {
            return replaceObject(object, position);
        }
        return false;
    }

    bool addObject(const DynamicAllocationData& object) {
        allocations.push_back(object);
        return true;
    }

    bool removeObject(const std::string& name) {
        auto it = std::find_if(allocations.begin(), allocations.end(),
            [&](const DynamicAllocationData& data) {
                return data.name == name;
            });

        if (it != allocations.end()) {
            allocations.erase(it);
            return true;
        }
        return false;
    }

    int getSizeByAddress(const std::string& addr) const {
        for (const auto& alloc : allocations) {
            if (alloc.address == addr) {
                return alloc.sizeAllocated;
            }
        }
        return -1;
    }
};

extern DynamicAllocation dynamicAllocation; // Global instance

extern int creatingMatrix, runningUserFunction, indexI, indexJ, _rf, higherPrecision, previousAnsType, matrixMode, numVectorLines, numVectorCols, check4Vector, vectorType, nrRoots, xATC, yATC, colsATC, linesATC, widthATC, heightATC, Pressed, toSendCommand, countSplits, maxExponent, numSysNum, * parentPol, replaceTimes, countEnters, countReturn, countBreak, Break, countUseReturn, countUseBreak, executedSolver, strStart, strEnd, rasf, processingOK, isFromMain, isFromSolveNow, verify, arG, feedbackValidation, isFromSolveNow, nPlaces, Mode, validVar, valid, valRenamedVar, synTest, count, continu, cleanhistory, rf, verified, verbose;
extern char* expr, * resp, * respR, * respI, * matrixValue, * returnCharArray, * saveUserFunctionsRenamedVariablesTextFile, * saveUserFunctionsVariablesTextFile, * saveScriptRenamedVariablesTextFile, * saveScriptVariablesTextFile, * saveRenamedVariablesTextFile, * saveRenamedTxtVariablesTextFile, * actualTime, * verboseRes, * numSys, * siPref, * context, * saveTxtVariablesTextFile, * saveVariablesTextFile, ** ansMatrices, * saveMatrixAns, * matrixResult, * vectorString, * customFolderPath, * saveATCPath, * renamedVariable, * dimensionsTxt, * windowTxt, * validChars, * lastCommand, * saveSimplified, * saveSimplification, * answers, * saveExpressionFF, * saveArithTrig, * saveExpressionF, * OutputText, * roots, * charMaster, * saveEquation, * atcPath, * calendarStr, * revariable, * varRename, * expressionF, * pathNAme, * variableSTring, * integral, * usRFunctions, * usRFuncTrans;
extern char** vectors;
extern char* forsprintf;
extern PrecisionValue** saveResultI, ** saveResultR;
extern PrecisionValue** vectorR, ** vectorI;
extern PrecisionValue* ans,* ansI;
extern PrecisionValue lastElement, lastElementI, LastDividerR, LastDividerI, lastDividerR, lastDividerI, natureValue;
extern PrecisionValue returnedR, returnedI, xValuesR,xValuesI, mINF, INF, ansRV, ansIV, resultR, resultI, resultFI;
extern int countDeleteorGetDynamic;
extern bool solvingExpression, haveCreatedDynamicMatrix, manageDynamicAllocations, toIntegrateOnCalculus, mainRoutine, checkMatrixIndex, useForVariables, notUseHigherPrecison, notSolved, variableControllersUsed, product, fromEquationSolver, progress, starting, studyFunction, I_O, isDivisible, solveMultiPoly, polySimplifier, physics, equationSolverRunning, solverRunning, solving, suppressVerboseResolution, retrySolver, retrySolver_2, retrySolver_3, returned, runningScript, equation_solver, poly;
template <typename T> T functionProcessor(char* trigon, PrecisionValue result, PrecisionValue amplitude, int res, char* argNotNumber);
template <typename T> T initialProcessor(char* arithTrig, T result);
template<typename T>
T arithSolver(char* trigon1, T result);
template<typename T>
T processVariable(char* variable);
template<typename T>
T binaryToDecimal(char* binary);
template<typename T>
T  octalToDecimal(char* octal);
template<typename T>
T hexadecimalToDecimal(char* hexadecimal);
template <typename T>
T convertToNumber(char* number);
template <typename T>
T main_core(char* arithTrig, char* fTrig, FILE* fout, char* path, T result1, T result2, int isFromMain);
template <typename T>
T main_sub_core(char* arithTrig, FILE* fout, int verify, char* path, int txt, char* variable, int v, int j, T result1, T result2, int isFromMain, int var, int valGet, int command);
template <typename T>
T solveNow(char* toSolveNow, T result1, T result2);
template <typename T>
T numericalSystems(char* numSystem);
template <typename T>
T calcNow(char* toCalc, T result1, T result2);
template <typename T>
T atcProg(char* expression);
template <typename T>
T calculateIntegral(T a, T b, char* function);
template<typename T>
T math_processor(char* expression);
template <typename T>
void getCharArray();
template <typename T>
T solve(char* equation);
template<typename T>
T solver(char* expression);
template<typename T>
bool tryEvaluateSolverFastPath(char* expression, T& solution);
PrecisionValue** getDynamic2DDoubleArray();
int autoComplete(char* query);
void readConsoleInputWithTabCompletion(char* line, int capacity);
template<typename T>
int variableValidator(char* variableFF);
template<typename T>
int matrixToValues(char* matrix, T result, T** values, T** valuesI, T** valuesS, T** valuesSI);
template<typename T>
int atcProgramming(char* script);
int strlength(char* stringV);
int countOccurrences(char* to_find, char* expression);
int deleteXOccurrences(char* to_find, char* expression, int x);
int getCorrectExponent(char* expression, char* maxExp, int maxExponent);
int linesNumber(char* values);
int colsNumber(char* values);
template<typename T>
void convertComplex2Exponential(T valueR, T valueI) {
    sprintf(respR, ""); sprintf(respI, "");
    sprintf(respR, "%s", convert2Exponential(valueR));
    sprintf(respI, "%s", convert2Exponential(valueI));
}
void getNumerationPol(char* expression);
template<typename T>
void simplifyPolynomial(char* expression);
void split(char* splitter, char* data);
template<typename T>
T solveMath(char* expression);
void printCounter();
void InstallCrashHandlers();
void putsAndPause(char* text);
void checkCPUFeatures();
void asciiOrder();
void CheckForNotDeleted();
void inverseAsciiOrder();
void autoAdjustWindow();
bool applyConsoleCommandDimensions(const char* setting);
bool applyConsoleDimensionsSafe(int columns, int lines);
bool applyConsoleWindowSafe(int x, int y, int width, int height);
void applyConsoleTitleSafe(const char* title);
void applyConsoleColorSafe(const char* colorCommand);
void repaintConsoleViewportSafe();
void maximizeConsoleWindowSafe();
void applyStartupConsoleLayoutSafe();
bool shouldUseLegacyConsoleWindowManagement();
void openNewATCInstance();
bool reduceExactRationalProductExpression(const char* expression, std::string& reducedExpression);
bool normalizeSolverCommandExpression(char* expression);
template <typename T>
void showSolutions(FILE* fout, int correct, T** valInd, T** valuesS, T** valuesSI, T** values, T** valuesI, T** valuesF, T** valuesFI);
void getDimensions();
template<typename T>
void ascendingOrder(char* values);
template<typename T>
void descendingOrder(char* values);
template<typename T>
void simpleSimplifyPolynomial(char* expression);
void variableController(char* variable);
template<typename T>
void manageExpression(char* arithTrig, T result1, T result2, int verify);
template<typename T>
void decimalToBinary(T decimal, char* path, int bp);
template<typename T>
void decimalToOctal(T decimal, char* path, int op);
template<typename T>
void decimalToHexadecimal(T decimal, char* path, int hp);
template <typename T>
void prefixDeterminator(T n, char* path);
void DayofWeek(int d, int m, int y, char* calendar);
void Calendar(char* yearCalendar, int year);
template<typename T>
void processor(int p, int i, int countL, int countR, char* arithTrig, char* matrix, FILE* fout, int correct, T result1);
void restoreWindowPosition();
void fft(char* values);
void ifft(char* values);
void variableRenamer(char* variable);
void print(char* data);
void simplifyExpression(char* expression);
void pathNameController(char* pathName, char* path);
void pathNameToPath(char* pathName);
template <typename T> void functionStudy(char* function);
void functionStudy(char* function);
void stringVariableController(char* stringVariable, char* string);
void stringVariableToString(char* stringVariable);
void renamer(char* expression);
template<typename T>
void variableToMultiply(char* expression);
template<typename T>
void toMultiply(char* expression, T result1, T result2);
template <typename T>
void print(char* text, T result1, T result2);
template <typename T>
void sprint(char* text, T result1, T result2);
void customFuncRenamer(char* variable);
template<typename T>
void designGraph(char* functionF);
template<typename T>
void mainType(char* value, char* toOpen, FILE* open, int argc, char* argv[]);
void replace(char* toReplace, char* replacement, char* string);
void replaceByIndex(char* toReplace, char* replacement, char* string, int index);
template<typename T> void fmsum(int lins, int cols, T** v, T** u, T** r, T** vI, T** uI, T** rI);
template<typename T> void fmsubt(int lins, int cols, T** v, T** u, T** r, T** vI, T** uI, T** rI);
void fmmulr(int lins, int cols, PrecisionValue** v, PrecisionValue** r, PrecisionValue re, PrecisionValue** vI, PrecisionValue** rI, PrecisionValue reI);
 template<typename T>
  void fmmulm(int lins2, int cols1, int lins1, int cols2, T** v, T** u, T** r, T** vI, T** uI, T** rI);
void saveToReport(char* report);
template <typename T>
T equationSolver(char* equation);
template <typename T>
void solveQuadraticEquation(char* arithTrig, T result1, T result2, int index);
void fmtranspose(int lins, int  cols, PrecisionValue** vMS, PrecisionValue** vMSI, PrecisionValue** mTransposeR, PrecisionValue** mTransposeI);
template<typename T>
void fmdeterminant(int lins, int  cols, T** vMS, T** vMSI);
void startDetProcessing(char* matrix);
void rootsToPolynomial(char* rooots);
template <typename T>
void fminverse(int lins, int  cols, T** vMS, T** vMSI, T** inverseR, T** inverseI);
void fmpowerm(PrecisionValue** v, PrecisionValue** vI, PrecisionValue** r, PrecisionValue** rI, int power, int lins, int cols);
template<typename T>
int fmrank(int lins, int cols, T** vMS, T** vMSI);
template<typename T>
void sum_polynomial(char* polynomial_1, char* polynomial_2);
template<typename T>
void sub_polynomial(char* polynomial_1, char* polynomial_2);
template<typename T>
void multi_polynomial(char* polynomial_1, char* polynomial_2);
template<typename T>

void div_polynomial(char* polynomial_1, char* polynomial_2);
void removeDuplPars(char* expression);

void removeTriplPars(char* expression);
void setWindow(int x, int y);
void setDimensions(int cols, int lines);
void convert2Vector(char* arithTrig);
void maximum(char* values);
void minimum(char* values);
void getCols(char* data);
void getLines(char* data);
void average(char* values);
void advancedSolver(char* expression);
void force_legacy_console_mode();
bool IsWindows11OrGreater();
bool shouldDisableATCIntroByDefault();
template<typename T>
void getRoots(T* expressionR, T* expressionI, T* rootsR, T* rootsI, int maxExponent, int rootIndex);
template<typename T>
const char* createMatrix(char* matrixName, int linsNumber, int colsNumber, char* mathExpression);
template <typename T>
bool fmdivm(int lins2, int cols1, int lins1, int cols2, T** v, T** u, T** vI, T** uI);
template<typename T>

bool simpleEvaluator(char* expression);
bool verifyForNumbers(char number);
template <typename T>
bool advancedEvaluator(char* expression);
bool isContainedVariable(char* to_find, char* string);
bool verifyPrefix(char* prefix);
bool verifyNumberExpression(char number);
template<typename T>
bool processTxt(char* path, int re);
template<typename T>
bool dataVerifier(char* data, T result1, T result2, int comment, int verify);
bool searchExtension(char* filename, char* extension);
template<typename T>
bool commands(char* expression, char* path, T result1, T result2, FILE* save);
bool atcFunctions(char* functionName);
bool isToWrite(char* arith);
bool isCommand(char* forTesting, char* command);
bool readyToSolve(char* paTh);
bool atcTestDisableExternalOpen();
void recordExternalOpen(const char* action, const char* target);
bool isEqual(char* to_find, char* string);
bool isContained(char* to_find, char* string);
bool isVariable(char* variable);
bool isContainedByIndex(char* to_find, char* string, int index);
bool verifyOperator(char operatorF);
bool verifyNumerator(char number);
bool isContainedInUserFunction(char* variable);
bool verifyCoefficient(char number);
bool verifyForNumber(char number);
void Created(const char* variableName, char* variableData);
bool verifyFraction(char number);
bool verifyMultiplication(char number);
template<typename T>
char* getDerivative(char* expression);
char* convertToString(char* string);
char* convertToString(char* string);
void GoToXY(int column, int line);
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
template <typename T>
char* convertVector2String(T** vectorR, T** vectorI, int numLines, int numCols);
template<typename T>
char* convert2Exponential(T value);
void check4Updates();
int* getDynamicIntArray();
void replaceLong(char* toReplace, char* replacement, char* string);
char* getDynamicCharArray(char* source, const char* variable);
char* getRenewDynamicCharArray(char* source, char** oldPointer);
char* getCorrectedDynamicCharArray(char** charArrayPointer);
void _delete(bool*& variable, char* variableName);
void _delete(int*& variable, char* variableName);
void _delete(char*& variable, const char* variableName);
template<typename T>
void _delete(T*& variable, char* variableName);
template<typename T>
void _Delete(T**& variable, int lines, int columns, char* variables);
void _Delete(char**& variable, int lines, int columns, char* variables);
char* getDynamicCharArrayLong(char* source);
char* getDynamicCharArray(int level, char* source, const char* variable);
void Created(const char* variableName, char* variableData);
void Deleted(const char* variableName);
void RegisterDynamicArray(void* variable, size_t elements);
size_t GetDynamicArraySize(const void* variable);
void UnregisterDynamicArray(void* variable);
void _deleteShort(char*& variable, const char* variableName);
char* getDynamicCharArrayShort(char* source, const char* variable);
void _deleteLong(char*& variable, const char* variableName);
char* getDynamicCharArrayFixedLenght(const char* source, size_t length);
char* getRenewDynamicCharArrayFixedLength(char* source, char** oldPointer, int size);
template <typename T>
void _Delete(T**& variable, int lines, char* variableName);
float getMemFactor1();
void _delete(PrecisionValue*& variable, char* variableName);

template <typename T>
inline T* getDynamicArray(size_t elements) {
    T* dynamicArray = new T[elements];
    RegisterDynamicArray(dynamicArray, elements);
    for (size_t i = 0; i < elements; ++i) {
        dynamicArray[i] = T(0);
    }
    return dynamicArray;
}

template <>
inline bool* getDynamicArray<bool>(size_t elements) {
    bool* dynamicArray = new bool[elements];
    RegisterDynamicArray(dynamicArray, elements);
    for (size_t i = 0; i < elements; ++i) {
        dynamicArray[i] = false;
    }
    return dynamicArray;
}

// Atualiza a assinatura previamente declarada para aceitar um parâmetro.
// Se existirem protótipos antigos, alinhar para: static void setMemFactor(float factor);
static void setMemFactor()
{
    float factor = -1.0f;
    float currentFactor = getMemFactor1();
    printf("\n\n==>Current factor is %f <==\n", currentFactor);
    do {
        
        puts("\n===>Please provide a factor value between 1.0 and 5.0");
        scanf("%f", &factor);

    } while (factor < 1.0 || factor>5.0);
    setMemFactor1(factor);
}

inline void _delete(PrecisionValue*& variable, char* variableName) {
    if (variable == nullptr) {
        return;
    }
    if (mainRoutine && manageDynamicAllocations) {
        Deleted(variableName);
    }
    size_t elements = GetDynamicArraySize(variable);
    if (elements == 0) {
        elements = DIMDOUBLE;
    }
    for (size_t i = 0; i < elements; ++i) {
        variable[i] = (higherPrecision == 1) ? PrecisionValue(mp_float(0)) : PrecisionValue(0.0);
    }
    UnregisterDynamicArray(variable);
    delete[] variable;
    variable = nullptr;
}


inline PrecisionValue* getDynamicDoubleArray(void) {
    PrecisionValue* dynamicArray = new PrecisionValue[DIMDOUBLE];
    RegisterDynamicArray(dynamicArray, DIMDOUBLE);
    for (int i = 0; i < DIMDOUBLE; i++) {
        dynamicArray[i] = (higherPrecision == 1) ? PrecisionValue(mp_float(0)) : PrecisionValue(0.0);
    }
    return dynamicArray;
}
static void applyMemFactor()
{
     memFactor = getMemFactor1();
    // Recalcula as dimensões do motor (variáveis já declaradas no header)
    // Usa static_cast para evitar warnings de conversão implícita
     if (memFactor >= 1.0 && memFactor <= 5.0) {
         DIM = static_cast<int>(3100 * memFactor);
         dime = static_cast<int>(1000 * memFactor);
         SHORTDIM = static_cast<int>(3100 * memFactor);
         LONGDIM = static_cast<int>(3100 * memFactor);
         DIMTWOD = static_cast<int>(150 * memFactor);
         DIMDOUBLE = static_cast<int>(1000 * memFactor);
     }
}

// Implementação de getter alinhado ao protótipo já declarado
static double getMemFactor()
{
    return static_cast<float>(memFactor);
}
