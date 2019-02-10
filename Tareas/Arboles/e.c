#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
	int id_proc;

	for (int i = 0; i < 2; i++)
	{
		if ((id_proc = fork()) == 0)
		{
			printf("Soy un proceso hijoA\n");
			if (i == 1)
			{
				for (int j = 0; j < 3; j++)
				{
					if ((id_proc = fork()) == 0)
					{
						printf("Soy un proceso hijoB\n");
						if (j == 0)
						{
							for (int k = 0; k < 3; k++)
							{
								if ((id_proc = fork()) == 0)
								{
									printf("Soy un proceso hijoC\n");
									if (k == 0)
									{
										for (int l = 0; l < 2; l++)
										{
											if ((id_proc = fork()) == 0)
											{
												printf("Soy un proceso hijoD\n");
												if (l == 0)
												{
													if ((id_proc = fork()) == 0)
													{
														printf("Soy un proceso hijoE\n");
														for (int m = 0; m < 2; m++)
														{
															if ((id_proc = fork()) == 0)
															{
																printf("Soy un proceso hijoF\n");
																if (m == 0)
																{
																	for (int n = 0; n < 3; n++)
																	{
																		if ((id_proc = fork()) == 0)
																		{
																			printf("Soy un proceso hijoG\n");
																			exit(0);
																		}
																	}
																}
																else if (m == 1)
																{
																	exit(0);
																}
																exit(0);
															}
														}
														exit(0);
													}
												}
												else if (l == 1)
												{
													if ((id_proc = fork()) == 0)
													{
														printf("Soy un proceso hijoH\n");
														for (int m = 0; m < 3; m++)
														{
															if ((id_proc = fork()) == 0)
															{
																printf("Soy un proceso hijoI\n");
																if (m == 2)
																{
																	for (int n = 0; n < 3; n++)
																	{
																		if ((id_proc = fork()) == 0)
																		{
																			printf("Soy un proceso hijoJ\n");
																			exit(0);
																		}
																	}
																}
																else
																{
																	exit(0);
																}
																exit(0);
															}
														}
														exit(0);
													}
												}
												exit(0);
											}
										}
									}
									else if (k == 1)
									{
										if ((id_proc = fork()) == 0)
										{
											printf("Soy un proceso hijoK\n");
											if ((id_proc = fork()) == 0)
											{
												printf("Soy un proceso hijoL\n");
												for (int l = 0; l < 4; l++)
												{
													if ((id_proc = fork()) == 0)
													{
														printf("Soy un proceso hijoM\n");
														if (l == 3)
														{
															for (int m = 0; m < 4; m++)
															{
																if ((id_proc = fork()) == 0)
																{
																	printf("Soy un proceso hijoN\n");
																	exit(0);
																}
															}
														}
														else
															exit(0);
														exit(0);
													}
												}
												exit(0);
											}
											else
												exit(0);
											exit(0);
										}
										else
											exit(0);
									}
									else if (k == 2)
									{
										if ((id_proc = fork()) == 0)
										{
											printf("Soy un proceso hijoO\n");
											exit(0);
										}
									}
									exit(0);
								}
							}
						}
						else if (j == 1)
						{
							for (int k = 0; k < 2; k++)
							{
								if ((id_proc = fork()) == 0)
								{
									printf("Soy un proceso hijoP\n");
									exit(0);
								}
							}
						}
						else if (j == 2)
						{
							if ((id_proc = fork()) == 0)
							{
								printf("Soy un proceso hijoQ\n");
								for (int k = 0; k < 2; k++)
								{
									if ((id_proc = fork()) == 0)
									{
										if (k == 0)
										{
											for (int l = 0; l < 2; l++)
											{
												if ((id_proc = fork()) == 0)
												{
													printf("Soy un proceso hijoR\n");
													if (l == 0)
													{
														for (int m = 0; m < 2; m++)
														{
															if ((id_proc = fork()) == 0)
															{
																printf("Soy un proceso hijoS\n");
																exit(0);
															}
														}
													}
													else if (l == 1)
													{
														for (int m = 0; m < 2; m++)
														{
															if ((id_proc = fork()) == 0)
															{
																printf("Soy un proceso hijoT\n");
																if (m == 0)
																	exit(0);
																else if (m == 1)
																{
																	for (int n = 0; n < 2; n++)
																	{
																		if ((id_proc = fork()) == 0)
																		{
																			printf("Soy un proceso hijoU\n");
																			exit(0);
																		}
																	}
																}
																exit(0);
															}
														}
													}
													exit(0);
												}
											}
										}
										else if (k == 1)
										{
											for (int l = 0; l < 3; l++)
											{
												if ((id_proc = fork()) == 0)
												{
													printf("Soy un proceso hijoV\n");
													if (l == 0)
													{
														exit(0);
													}
													else if (l == 1)
													{
														for (int m = 0; m < 3; m++)
														{
															if ((id_proc = fork()) == 0)
															{
																printf("Soy un proceso hijoW\n");
																if (m == 0)
																{
																	exit(0);
																}
																else if (m == 1)
																{
																	for (int n = 0; n < 3; n++)
																	{
																		if ((id_proc = fork()) == 0)
																		{
																			printf("Soy un proceso hijoX\n");
																			exit(0);
																		}
																	}
																}
																else if (m == 2)
																{
																	exit(0);
																}
																exit(0);
															}
														}
													}
													else if (l == 2)
													{
														for (int m = 0; m < 2; m++)
														{
															if ((id_proc = fork()) == 0)
															{
																printf("Soy un proceso hijoY\n");
																if (m == 0)
																{
																	exit(0);
																}
																else if (m == 1)
																{
																	for (int n = 0; n < 2; n++)
																	{
																		if ((id_proc = fork()) == 0)
																		{
																			printf("Soy un proceso hijoZ\n");
																			exit(0);
																		}
																	}
																}
																exit(0);
															}
														}
													}
													exit(0);
												}
											}
										}
										exit(0);
									}
								}
								exit(0);
							}
						}
						exit(0);
					}
				}
			}
		}
		else
			exit(0);
	}
	exit(0);
}