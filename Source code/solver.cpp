#include "stdafx.h"

double xValuesR = 0, xValuesI = 0;
boolean solverRunning = false, realSolver = false;

double solverReal(char expression[DIM]) {
	char equation[DIM] = "", saveEquation[DIM] = "";
	sprintf(equation, "%s", expression);
	char const * equationF = equation;
	double precision = 0.1, resultFR = -1, resultFI = 0, savePrecision = 0.1, saveResult = -1, time_s = 0, time_ms = 0, save_time = 0, saveValue = 0;
	char Xequal[100] = "";
	int waitTime = 10;
	clock_t start, end;
	resultR = resultFR;
	resultI = resultFI;
	start = clock();
	boolean to_solve = dataVerifier(equation, 0, 0, 1, 1);
	if (to_solve) {
		while (time_s < waitTime && resultR != 0 && precision > 1E-15) {
			saveResult = saveResult * 10;
			savePrecision = savePrecision * 10;
			precision = savePrecision;
			resultFR = saveResult;
			while (resultR != 0 && precision > 1E-15&&time_s < waitTime && resultFR < (saveResult*-1)) {
				xValuesR = resultFR; xValuesI = resultFI;
				sprintf(equation, "%s", equationF);
				calcNow(equation, 0, 0);
				if (resultR < 0) {
					do {
						if (resultR < 0) {
							resultFR = resultFR + precision;
							xValuesR = resultFR; xValuesI = resultFI;
							sprintf(equation, "%s", equationF);
							calcNow(equation, 0, 0);
						}
						if (resultR > 0) {
							resultFR = resultFR - precision;
							precision = precision / 10;
							xValuesR = resultFR; xValuesI = resultFI;
							sprintf(equation, "%s", equationF);
							calcNow(equation, 0, 0);
						}
						end = clock();
						time_ms = (end - start) / (CLOCKS_PER_SEC / 1000);
						time_s = qu(time_ms, 1000);
						if (save_time != time_s) {
							save_time = time_s;
						}
					} while (resultR != 0 && precision > 1E-15&&time_s < waitTime && resultFR < (saveResult*-1));
				}
				else {
					do {
						if (resultR > 0) {
							resultFR = resultFR + precision;
							xValuesR = resultFR; xValuesI = resultFI;
							sprintf(equation, "%s", equationF);
							calcNow(equation, 0, 0);
						}
						else {
							if (resultR < 0) {
								resultFR = resultFR - precision;
								precision = precision / 10;
								xValuesR = resultFR; xValuesI = resultFI;
								sprintf(equation, "%s", equationF);
								calcNow(equation, 0, 0);
							}
						}
						end = clock();
						time_ms = (end - start) / (CLOCKS_PER_SEC / 1000);
						time_s = qu(time_ms, 1000);
						if (save_time != time_s) {
							save_time = time_s;
						}
					} while (resultR != 0 && precision > 1E-15&&time_s < waitTime && resultFR < (saveResult*-1));

				}
				if (time_s >= waitTime) {
					char checkComplex[DIM] = "";
					sprintf(checkComplex, "%s", equationF);
					solver(checkComplex);
				}
				else {
					if (resultR <0.1 && resultR>-0.1) {
						resultR = resultFR; resultI = resultFI;
						return resultFR;
					}
				}
			}
		}
	}
	else {
		puts("\n\nYour expression has errors.\n\n");
		return NULL;
	}
	return NULL;
}

double solver(char expression[DIM]) {
	char equation[DIM] = "", saveEquation[DIM] = "";
	sprintf(equation, "%s", expression);
	char const * equationF = equation;
	double precisionR = 0.01, precisionI = 0.01, saveResultR = -1, savePrecisionR = 0.01, resultFR = -1, saveResultI = -1, savePrecisionI = 0.01, resultFI = -1;
	int count = 0, countMax = 100;
	resultR = resultFR;
	resultI = resultFI;
	boolean to_solve = dataVerifier(equation, 0, 0, 1, 1);
	if (to_solve) {
		if (isContained(")res^", equation) && isContained("i", equation) && expression[strEnd - 1] != 'p' || isContained("(res)", equation)) {
			solverReal(equation);
			if (resultR != 0) {
				realSolver = true;
				return resultR;
			}
		}
		else {
			realSolver = false;
			while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax) {
				saveResultR = saveResultR * 10;
				savePrecisionR = savePrecisionR * 10;
				precisionR = savePrecisionR;
				resultFR = saveResultR;
				saveResultI = saveResultI * 10;
				savePrecisionI = savePrecisionI * 10;
				precisionI = savePrecisionI;
				resultFI = saveResultI;
				while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1)) {
					xValuesR = resultFR; xValuesI = resultFI;
					sprintf(equation, "%s", equationF);
					calcNow(equation, 0, 0);
					saveResultR = resultR; saveResultI = resultI;
					if (resultR < 0 && resultI < 0) {
						do {
							if (resultR < 0 && resultI < 0) {
								do {
									resultFR = resultFR + precisionR;
									resultFI = resultFI + precisionI;
									xValuesR = resultFR; xValuesI = resultFI;
									sprintf(equation, "%s", equationF);
									calcNow(equation, 0, 0);
									saveResultR = resultR; saveResultI = resultI;
									count++;
								} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
							}
							else {
								if (resultR > 0 && resultI > 0) {
									do {
										resultFR = resultFR - precisionR;
										precisionR = precisionR / 10;
										resultFI = resultI - precisionI;
										precisionI = precisionI / 10;
										xValuesR = resultFR; xValuesI = resultFI;
										sprintf(equation, "%s", equationF);
										calcNow(equation, 0, 0);
										saveResultR = resultR; saveResultI = resultI;
										count++;
									} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
								}
								else {
									if (resultR < 0 && resultI > 0) {
										do {
											resultFR = resultFR + precisionR;
											resultFI = resultFI - precisionI;
											precisionI = precisionI / 10;
											xValuesR = resultFR; xValuesI = resultFI;
											sprintf(equation, "%s", equationF);
											calcNow(equation, 0, 0);
											saveResultR = resultR; saveResultI = resultI;
											count++;
										} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
									}
									else {
										if (resultR > 0 && resultI < 0) {
											do {
												resultFR = resultFR - precisionR;
												precisionR = precisionR / 10;
												resultFI = resultFI + precisionI;
												xValuesR = resultFR; xValuesI = resultFI;
												sprintf(equation, "%s", equationF);
												calcNow(equation, 0, 0);
												saveResultR = resultR; saveResultI = resultI;
												count++;
											} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
										}
									}
								}
							}
							count++;
						} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax);
					}
					else {
						if (resultR > 0 && resultI > 0) {
							do {
								if (resultR > 0 && resultI > 0) {
									do {
										resultFR = resultFR - precisionR;
										precisionR = precisionR / 10;
										resultFI = resultFI - precisionI;
										precisionI = precisionI / 10;
										xValuesR = resultFR; xValuesI = resultFI;
										sprintf(equation, "%s", equationF);
										calcNow(equation, 0, 0);
										saveResultR = resultR; saveResultI = resultI;
										count++;
									} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
								}
								else {
									if (resultR < 0 && resultI < 0) {
										do {
											resultFR = resultFR + precisionR;
											resultFI = resultFI + precisionI;
											xValuesR = resultFR; xValuesI = resultFI;
											sprintf(equation, "%s", equationF);
											calcNow(equation, 0, 0);
											saveResultR = resultR; saveResultI = resultI;
											count++;
										} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
									}
									else {
										if (resultR < 0 && resultI > 0) {
											do {
												resultFR = resultFR + precisionR;
												resultFI = resultFI - precisionI;
												precisionI = precisionI / 10;
												xValuesR = resultFR; xValuesI = resultFI;
												sprintf(equation, "%s", equationF);
												calcNow(equation, 0, 0);
												saveResultR = resultR; saveResultI = resultI;
												count++;
											} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
										}
										else {
											if (resultR > 0 && resultI < 0) {
												do {
													resultFR = resultFR - precisionR;
													precisionR = precisionR / 10;
													resultFI = resultFI + precisionI;
													xValuesR = resultFR; xValuesI = resultFI;
													sprintf(equation, "%s", equationF);
													calcNow(equation, 0, 0);
													saveResultR = resultR; saveResultI = resultI;
													count++;
												} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
											}
										}
									}
								}
								count++;
							} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
						}
						else {
							if (resultR < 0 && resultI > 0) {
								do {
									if (resultR < 0 && resultI < 0) {
										do {
											resultFR = resultFR + precisionR;
											resultFI = resultFI + precisionI;
											xValuesR = resultFR; xValuesI = resultFI;
											sprintf(equation, "%s", equationF);
											calcNow(equation, 0, 0);
											saveResultR = resultR; saveResultI = resultI;
											count++;
										} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
									}
									else {
										if (resultR > 0 && resultI > 0) {
											do {
												resultFR = resultFR - precisionR;
												precisionR = precisionR / 10;
												resultFI = resultI - precisionI;
												precisionI = precisionI / 10;
												xValuesR = resultFR; xValuesI = resultFI;
												sprintf(equation, "%s", equationF);
												calcNow(equation, 0, 0);
												saveResultR = resultR; saveResultI = resultI;
												count++;
											} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
										}
										else {
											if (resultR < 0 && resultI > 0) {
												do {
													resultFR = resultFR + precisionR;
													resultFI = resultFI - precisionI;
													precisionI = precisionI / 10;
													xValuesR = resultFR; xValuesI = resultFI;
													sprintf(equation, "%s", equationF);
													calcNow(equation, 0, 0);
													saveResultR = resultR; saveResultI = resultI;
													count++;
												} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
											}
											else {
												if (resultR > 0 && resultI < 0) {
													do {
														resultFR = resultFR - precisionR;
														precisionR = precisionR / 10;
														resultFI = resultFI + precisionI;
														xValuesR = resultFR; xValuesI = resultFI;
														sprintf(equation, "%s", equationF);
														calcNow(equation, 0, 0);
														saveResultR = resultR; saveResultI = resultI;
														count++;
													} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
												}
											}
										}
									}
									count++;
								} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
							}
							else {
								if (resultR > 0 && resultI < 0) {
									do {
										if (resultR > 0 && resultI > 0) {
											do {
												resultFR = resultFR - precisionR;
												precisionR = precisionR / 10;
												resultFI = resultFI - precisionI;
												precisionI = precisionI / 10;
												xValuesR = resultFR; xValuesI = resultFI;
												sprintf(equation, "%s", equationF);
												calcNow(equation, 0, 0);
												saveResultR = resultR; saveResultI = resultI;
												count++;
											} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
										}
										else {
											if (resultR < 0 && resultI < 0) {
												do {
													resultFR = resultFR + precisionR;
													resultFI = resultFI + precisionI;
													xValuesR = resultFR; xValuesI = resultFI;
													sprintf(equation, "%s", equationF);
													calcNow(equation, 0, 0);
													saveResultR = resultR; saveResultI = resultI;
													count++;
												} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
											}
											else {
												if (resultR < 0 && resultI > 0) {
													do {
														resultFR = resultFR + precisionR;
														resultFI = resultFI - precisionI;
														precisionI = precisionI / 10;
														xValuesR = resultFR; xValuesI = resultFI;
														sprintf(equation, "%s", equationF);
														calcNow(equation, 0, 0);
														saveResultR = resultR; saveResultI = resultI;
														count++;
													} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
												}
												else {
													if (resultR > 0 && resultI < 0) {
														do {
															resultFR = resultFR - precisionR;
															precisionR = precisionR / 10;
															resultFI = resultFI + precisionI;
															xValuesR = resultFR; xValuesI = resultFI;
															sprintf(equation, "%s", equationF);
															calcNow(equation, 0, 0);
															saveResultR = resultR; saveResultI = resultI;
															count++;
														} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
													}
												}
											}
										}
										count++;
									} while ((saveResultR == 0 && saveResultI == 0) == false && count < countMax&& resultFR < (saveResultR*-1) && resultFI < (saveResultI*-1));
								}
							}
						}
					}
					count++;
				}
				if (saveResultR > -0.1&&saveResultR<0.1 && saveResultI> -0.1&&saveResultI < 0.1 && count >= countMax) {
					resultR = saveResultR; resultI = saveResultI;
					if (resultR == 0) {
						resultR = solverReal(equation);
						if (resultR != 0) {
							return resultR;
						}
						else {
							return NULL;
						}
					}
					return resultR;
				}
				count++;
			}
		}
	}
	else {
		puts("\n\nYour expression has errors.\n\n");
		return NULL;
	}
	if (resultR == 0) {
		solverReal(expression);
		if (resultR != 0) {
			return resultR;
		}
		else {
			return NULL;
		}
	}
	return NULL;
}
