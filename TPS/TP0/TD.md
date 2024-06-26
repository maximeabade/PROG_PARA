# TD 0 - Introduction à l'architecture de programmation parallèle
## 1
 en passant par le code assembleur on remarquera qu'un ordi utilise
un système CISC alors que l'autre utilise un RISC, CISCétant la surement 
meilleur

example:
RISC vs CISC
x86 vs ARM
donc on ne peut pas tout simplement comparé le temps de résolution que sur le 
nombre de MIPS

## 2.
 1 000 000/40 = 25 000 
CPI=(cycles/instructions)

## 3.
 IPC = intruction par cycle
ou  IPC = 35 000 / 17 000 =  2.059

## 4.
  time = nCrorale*10-6sec = 1.04 sec
    
    nCyclefp = 200 000 * 10 *0.6 = 800000
    nCycleautre = 200 000 *40 =  240 000
    nCycletotal== 1 040 000

## 5.
  a. 100/x = 1/( 0.1 + 0.9/10 ) => x=19sec
speed up = ancien temps / nouveau temps = 1/( FS+ FP/s) [cf p.41 du pdf]
    FS = 1-FP

s = nombre de coeur, s est quelque chose qui a été amélioré
par example

    90+10 = 100sec 
    9+10 = 19

    b. S= 100/19=5.26 (pas d'unité on divise un temps par un temps,
    il s'agit d'une amélioration)

    c. la fraction que prend le temps amélioré sur dans le système est de 
        9/19=0.47 => elle prend donc maintenant 47% du temps
        alors qu'avanat elle prenais 90% du temps

## 6. 
 20/100 * 2 = 0.4
    70/100 * 1.3 = 0.91
on prefère donc utilise une amélioration de performance de 1.3 qui est utilisé 70% du temps
S= 1 /(1/(fs+fp/s))
 a. s=2 fp=0.2      S = 1 / (0.8+0.2/2) = 1/tnew = 0.9 <--- il s'agit de tnew
 b. s=1.3 fp=0.7    S = 1 / (0.3+0.7/1.3) = 1/tnew = 0.84 <-- meilleur temps 


## 7. 
 S = 1 / (1/ (fs+ fp/s)) 
    ==> 1.2 = 1 / (0.6+0.4/s) ==> s = 1.71  pour une amélioration de 20%
    ==> 1.6 = 1 / (0.6+0.4/s) ==> s = 16 c'est énorme et c'est que pour une amélioration du système global de 60% 
il vaut mieux améliorer toutes les sous-système que d'améliorer un seul

## 8. 
S = Told / Tnew = 1 / (Fs + Fp/s) = 1 / (0.2 + 0.1/4) = 2.5


## 9.
S = Told / Tnew = 1 / (Fs + Fp/s) = 1 / (0.1 + 0.9/4) = 3.08

## 10.
S = 1 / ((0.2 + 0.8/4)*0.6 + 0.4)    le 60% vient de l énoncé <br>
        PREMIER PROCESSUS    2ND PROCESSUS NON PARALLELISÉ                                  
## 11.
S = 1 / (( (0.2 + 0.8/4)*0.6 + (0.1 + 0.9/4)*0.4))  = 2.70 <br>
        PREMIER PROCESSUS   2ND PROCESSUS PARALLELISÉ <br>
        60% des ressources  40% des ressources

Efficacité = S/p = 2.70/4 = 0.675 = 67.5%


## 12. On ignore la consigne, on suppose que les deux processus sont parallelisés

### 12 CORES: 
    S = 4.35 ; Efficacité = 4.35/12 = 0.3625 = 36%
### 24 CORES:
    S = 5.13 ; Efficacité = 5.13/24 = 0.21375 = 21%

<img src="./img/graph.png"></img>

## 13.
    4Cores  -> 1000/2.70 = 370.37€ par amélioration
    12Cores -> 2500/4.35 = 574.71€ par amélioration
    24Cores -> 6000/5.13 = 1169.59€ par amélioration

## 14. Calcul du speedup maximum possible
S = 1/(0.3 + 0.7/p) ==> Smax = Lim(p->inf) 1/(0.3 + 0.7/p) = 1/0.3 = 3.33

Smax = Told / Tnew = 1000 / (0.3*1000) = 3.33

<img src = "./img/graph2.png"></img>

## 15.
### EQUATION DE Amdahl avec perte de 5 secondes par processus ajoutés
S = Told / Tnew = Tsequentiel / Tparallele = 1000 /(0.3x1000 + 700/p + 5x(p-1)) 

Tnew = 5p² + 295p + 700

<img src="./img/graph3.png"></img>

## 17.

S = (1-Fp) + S*Fp = 1 + (S-1) * Fp

FractionSéquentielle Fs = 0.05
FractionParallèle Fp = 0.95

S10 = 1 + (10-1) * 0.95 = 9.55
S14 = 1 + (14-1) * 0.95 = 13.35

P = 10 -> W(charge de travail) = W * Fs + W * Fp = W(0.05 + 0.95)
P = 14 -> W' = WxFs = W * Fp * DeltaP= W(0.05 + 0.95(14-10))

W'/W = (0.05 + 0.95*4) / (0.05 + 0.95) = 3.85

