#ifndef LECTURAOPERACION_H_INCLUDED
#define LECTURAOPERACION_H_INCLUDED

void leerArchivo(RALineal *ral, RACuadratico *rac, ArbolBB *abb, lista *lso, lista *lsobt){
    int codOp, exito, exitoRAC;
    int cantAltaLSO = 0, cantAltaLSOBT = 0, cantAltaABB = 0;
    int cantBajaLSO = 0, cantBajaLSOBT = 0, cantBajaABB = 0;
    int cantEvocExLSO = 0, cantEvocExLSOBT = 0, cantEvocExRAL = 0, cantEvocExRAC = 0, cantEvocExABB = 0;
    int cantEvocNELSO = 0, cantEvocNELSOBT = 0, cantEvocNERAL = 0, cantEvocNERAC = 0, cantEvocNEABB = 0;
    int sumCorrimientosAltaLSO = 0, sumCorrimientosAltaBT = 0, sumCorrimientosBajaLSO = 0, sumCorrimientosBajaBT = 0, sumModPtrAlta = 0, sumModPtrBaja = 0;
    int maxCorrAltaLSO = 0, maxCorrAltaBT = 0, maxCorrBajaLSO = 0, maxCorrBajaBT = 0, maxModPtrAlta = 0, maxModPtrBaja = 0;
    int consultasLSO = 0, consultasBT = 0, consultasABB = 0, consultasRAL = 0, consultasRAC = 0;
    int consultasLSONE = 0, consultasBTNE = 0, consultasABBNE = 0, consultasRALNE = 0, consultasRACNE = 0;
    int maxConsLSO = 0, maxConsBT = 0, maxConsABB = 0, maxConsRAL = 0, maxConsRAC = 0;
    int maxConsLSONE = 0, maxConsBTNE = 0, maxConsABBNE = 0, maxConsRALNE = 0, maxConsRACNE = 0;
    float medCorrimientosAltaLSO, medCorrimientosBajaLSO, medCorrimientosAltaBT, medCorrimientosBajaBT, medModPtrAlta, medModPtrBaja;
    float medEvocLSO, medEvocBT, medEvocABB, medEvocRAL, medEvocRAC;
    float medEvocLSONE, medEvocBTNE, medEvocABBNE, medEvocRALNE, medEvocRACNE;
    Articulo evocacion, auxEvoc;
    char codigo[10];


    FILE *fp;

    if((fp = fopen("MiTest.txt", "r")) == NULL){
        printf("ERROR: No se pudo abrir el archivo\n");
        system("pause");
    }
    else{
        codOp = 0;

        while(!(feof(fp))){

            fscanf(fp, "%d", &codOp);
            fgetc(fp);
            fscanf(fp,"%[^\n]s",&auxArt.codigo);
            fgetc(fp);

            if(codOp == 1 || codOp == 2){
                fscanf(fp, "%[^\n]s", &auxArt.tipo);
                fgetc(fp);
                fscanf(fp, "%[^\n]s", &auxArt.marca);
                fgetc(fp);
                fscanf(fp, "%[^\n]s", &auxArt.descripcion);
                fgetc(fp);
                fscanf(fp, "%f", &auxArt.precio);
                fgetc(fp);
                fscanf(fp, "%d", &auxArt.cantidad);
                fgetc(fp);

                if(codOp == 1){//Llama las altas
                    if (lso->ult+1 != MAX){
                        altaLSO(lso, auxArt, &exito);
                        if (exito == 1){
                            sumCorrimientosAltaLSO = sumCorrimientosAltaLSO + corrimientos;
                            if (corrimientos > maxCorrAltaLSO)
                                maxCorrAltaLSO = corrimientos;
                            cantAltaLSO++;
                        }
                    }
                    if (lsobt->ult+1 != MAX){
                        altaLSOBT(lsobt, auxArt, &exito);
                        if (exito == 1){
                            sumCorrimientosAltaBT = sumCorrimientosAltaBT + corrimientos;
                            if (corrimientos > maxCorrAltaBT)
                                maxCorrAltaBT = corrimientos;
                            cantAltaLSOBT++;
                        }
                    }
                    exito = altaABB(abb, auxArt);
                    if (exito == 1){
                        sumModPtrAlta = sumModPtrAlta + modificaPtr;
                        if (modificaPtr > maxModPtrAlta)
                            maxModPtrAlta = modificaPtr;
                        cantAltaABB++;
                    }
                    if (ral->cantidad != M_RAL){
                        altaRAL(ral, auxArt, &exito);
                    }
                    if (rac->cantidad != M_RAC){
                        altaRAC(rac, auxArt, &exitoRAC);
                    }
                }
                else{//Llama a las bajas
                    bajaLSO(lso, auxArt.codigo, &exito);
                    if (exito == 1){
                        sumCorrimientosBajaLSO = sumCorrimientosBajaLSO + corrimientos;
                        if (corrimientos > maxCorrBajaLSO)
                            maxCorrBajaLSO = corrimientos;
                        cantBajaLSO++;
                    }
                    bajaLSOBT(lsobt, auxArt.codigo, &exito);
                    if (exito == 1){
                        sumCorrimientosBajaBT = sumCorrimientosBajaBT + corrimientos;
                        if (corrimientos > maxCorrBajaBT)
                            maxCorrBajaBT = corrimientos;
                        cantBajaLSOBT++;
                    }
                    exito = bajaABB(abb, auxArt.codigo);
                    if (exito == 1){
                        sumModPtrBaja = sumModPtrBaja + modificaPtr;
                        if (modificaPtr > maxModPtrBaja)
                            maxModPtrBaja = modificaPtr;
                        cantBajaABB++;
                    }
                    bajaRAL(ral, auxArt.codigo, &exito);
                    bajaRAC(rac, auxArt.codigo, &exito);

                }
            }
            else{
                strcpy(&evocacion.codigo, &auxArt.codigo);
                strcpy(&codigo, auxArt.codigo);

                evocarLSO(*lso, codigo, &exito);
                if(exito == 1){
                    consultasLSO = consultasLSO + consultas;
                    if (consultas > maxConsLSO)
                        maxConsLSO = consultas;
                    cantEvocExLSO++;
                }
                else{
                    consultasLSONE = consultasLSONE + consultas;
                    if (consultas > maxConsLSONE)
                        maxConsLSONE = consultas;
                    cantEvocNELSO++;
                }
                evocarLSOBT(lsobt, auxArt.codigo, &exito);
                if (exito == 1){
                    consultasBT = consultasBT + consultas;
                    if (consultas > maxConsBT)
                        maxConsBT = consultas;
                    cantEvocExLSOBT++;
                }
                else{
                    consultasBTNE = consultasBTNE + consultas;
                    if (consultas > maxConsBTNE)
                        maxConsBTNE = consultas;
                    cantEvocNELSOBT++;
                }
                exito = evocarABB(abb, &evocacion);
                if(exito == 1){
                    consultasABB = consultasABB + consultas;
                    if (consultas > maxConsABB)
                        maxConsABB = consultas;
                    cantEvocExABB++;
                }
                else{
                    consultasABBNE = consultasABBNE + consultas;
                    if (consultas > maxConsABBNE)
                        maxConsABBNE = consultas;
                    cantEvocNEABB++;
                }
                evocarRAL(*ral, auxArt.codigo, &exito, &evocacion);
                if(exito == 1){
                    consultasRAL = consultasRAL + consultas;
                    if (consultas > maxConsRAL)
                        maxConsRAL = consultas;
                    cantEvocExRAL++;
                }
                else{
                    consultasRALNE = consultasRALNE + consultas;
                    if (consultas > maxConsRALNE)
                        maxConsRALNE = consultas;
                    cantEvocNERAL++;
                }
                evocarRAC(*rac, auxArt.codigo, &exito, &evocacion);
                if (exito == 1){
                    consultasRAC = consultasRAC + consultas;
                    if (consultas > maxConsRAC)
                        maxConsRAC = consultas;
                    cantEvocExRAC++;
                }
                else{
                    consultasRACNE = consultasRACNE + consultas;
                    if (consultas > maxConsRACNE)
                        maxConsRACNE = consultas;
                    cantEvocNERAC++;
                }
            }
        }
        fclose(fp);
        medEvocLSO = (float)consultasLSO/cantEvocExLSO;
        medEvocLSONE = (float)consultasLSONE/cantEvocNELSO;
        medEvocBT = (float)consultasBT/cantEvocExLSOBT;
        medEvocBTNE = (float)consultasBTNE/cantEvocNELSOBT;
        medEvocABB = (float)consultasABB/cantEvocExABB;
        medEvocABBNE = (float)consultasABBNE/cantEvocNEABB;
        medEvocRAL = (float)consultasRAL/cantEvocExRAL;
        medEvocRALNE = (float)consultasRALNE/cantEvocNERAL;
        medEvocRAC = (float)consultasRAC/cantEvocExRAC;
        medEvocRACNE = (float)consultasRACNE/cantEvocNERAC;
        medCorrimientosAltaLSO = (float)sumCorrimientosAltaLSO/cantAltaLSO;
        medCorrimientosAltaBT = (float)sumCorrimientosAltaBT/cantAltaLSOBT;
        medModPtrAlta = (float)sumModPtrAlta/cantAltaABB;
        medCorrimientosBajaLSO = (float)sumCorrimientosBajaLSO/cantBajaLSO;
        medCorrimientosBajaBT = (float)sumCorrimientosBajaBT/cantBajaLSOBT;
        medModPtrBaja = (float)sumModPtrBaja/cantBajaABB;

        printf("\n           |      EVOC EX       |     EVOC NO EX     |        ALTA        |        BAJA        |\n");
        printf(" ESTRUCTURA|--------------------|--------------------|--------------------|--------------------|\n");
        printf("           |    MAX   |   MED   |    MAX   |   MED   |    MAX   |   MED   |    MAX   |   MED   |\n");
        printf("-----------|----------|---------|----------|---------|----------|---------|----------|---------|\n");
        printf(" LSO            %d       %.2f        %d       %.2f        %d        %.2f       %d       %.2f    \n", maxConsLSO, medEvocLSO, maxConsLSONE, medEvocLSONE, maxCorrAltaLSO, medCorrimientosAltaLSO, maxCorrBajaLSO, medCorrimientosBajaLSO);
        printf("-----------|----------|---------|----------|---------|----------|---------|----------|---------|\n");
        printf(" LSOBT           %d        %.2f        %d       %.2f        %d        %.2f       %d       %.2f    \n", maxConsBT, medEvocBT, maxConsBTNE, medEvocBTNE, maxCorrAltaBT, medCorrimientosAltaBT, maxCorrBajaBT, medCorrimientosBajaBT);
        printf("-----------|----------|---------|----------|---------|----------|---------|----------|---------|\n");
        printf(" ABB            %d        %.2f        %d       %.2f         %d        %.2f        %d        %.2f    \n", maxConsABB, medEvocABB, maxConsABBNE, medEvocABBNE, maxModPtrAlta, medModPtrAlta, maxModPtrBaja, medModPtrBaja);
        printf("-----------|----------|---------|----------|---------|----------|---------|----------|---------|\n");
        printf(" RAL             %d        %.2f        %d       %.2f         0         0          0         0    \n", maxConsRAL, medEvocRAL, maxConsRALNE, medEvocRALNE);
        printf("-----------|----------|---------|----------|---------|----------|---------|----------|---------|\n");
        printf(" RAC             %d        %.2f        %d       %.2f         0         0          0         0    \n", maxConsRAC, medEvocRAC, maxConsRACNE, medEvocRACNE);
        printf("------------------------------------------------------------------------------------------------\n\n");

        system("pause");
    }
}

#endif // LECTURAOPERACION_H_INCLUDED
