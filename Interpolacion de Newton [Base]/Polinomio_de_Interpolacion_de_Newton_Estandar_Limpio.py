import numpy as np
from sympy import symbols, expand

'''Programa que forma parte del proyecto final de Metodos Numéricos asociado al tema correspondiente: Polinomios de Iterpolación Numérica.
Este programa es concretamente parte del metodo de interpolación de Newton, más especificamente: Polinomio de Interpolacion de Newton en su
forma estandar. El ejemplo presentado en este programa fue presentado en clases, es un ejemplo sencillo que tiene por objetivo mostrar los pasos
para realizar este metodo de interpolación'''

print('\n---------------------------------------------------------------------')
print('\nMetodo de Interpolacion de Newton en su forma base')

print('\n---------------------------------------------------------------------')
print('\nEjemplo presentado en clases:')
print('\n---------------------------------------------------------------------')

print('\nDe una función F(x), conocemos la información de la tabla presentada a continuación:')
print('\n-----------------------------------------------------------------------------')
print(f"{'x':^8} {'0':^4} {'0.1':^8} {'0.2':^8} {'0.3':^8} {'0.4':^8} {'0.5':^8} {'0.6':^8} {'0.7':^8}")
print(f"\n{'F(x)':^8} {'0.3':^4} {'0.31':^8} {'0.32':^8} {'0.33':^8} {'0.34':^8} {'0.45':^8} {'0.46':^8} {'0.47':^8}")
print('-----------------------------------------------------------------------------')
print('\nInterpolar F(0.35) utilizando el polinomio de interpolación de Newton P3(x).')

valores_x = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7]
valores_fx = [0.3, 0.31, 0.32, 0.33, 0.34, 0.45, 0.46, 0.47]
valor_a_interpolar = 0.35

def newton_base(X, FX):
    
    x = X
    fx = FX
    
    polinomio = []
    polinomio.append(fx[0])
    
    primer_resultado = []
    
    matriz = np.column_stack((x, fx))
    agregar_a_matriz = []
    
    tamaño = len(x)
    
    ite = 1
    c = 1
    
    while tamaño > 1:
        
        if(ite == 1):
            
            for i in range(1, tamaño):
                resultados = round((fx[i] - fx[i-1]) / (x[i] - x[i-1]), 3)
                #print('iteracion: ', i)
                primer_resultado.append(resultados)
            agregar_a_matriz = ['-'] * ite + primer_resultado
            matriz = np.column_stack((matriz, agregar_a_matriz))
            
        elif(ite > 1):
            
            for i in range(1, tamaño):
                resultados = round((fx[i] - fx[i-1]) / (x[i+c] - x[i-1]), 3)
                #print('iteracion: ', i)
                primer_resultado.append(resultados)
            c +=1
            
            agregar_a_matriz = ['-'] * ite + primer_resultado
            matriz = np.column_stack((matriz, agregar_a_matriz))
            
        polinomio.append(primer_resultado[0])
        
        fx = primer_resultado
        primer_resultado = []
        
        ite += 1
        tamaño -= 1
        
    str_matriz = str(matriz)
    
    print('---------------------------')
    print('\nTabla de Resultados')
    print('---------------------------')
    print(f"{'i':^8} {'x':^8} {'F(x)':^8}")
    print('---------------------------')
    
    for fila in matriz:
        print(' '.join(f"{' ' if i >1 else '  '}{str(elem): <7}" for i, elem in enumerate(fila)))
    
    print('\n---------------------------')
    print('\nDiferencias: ', polinomio)
    print('\n---------------------------\n')
    
    construir_polinomio(x, polinomio)


def construir_polinomio(valores_x, polinomio):
    print(polinomio)
    x = symbols('x')
    n = len(valores_x)
    polinomio_newton = polinomio[0]  # Inicializar el polinomio con el término constante
    for i in range(1, n):
        termino = polinomio[i]
        for j in range(i):
            termino *= (x - valores_x[j])
        polinomio_newton += termino
        
    
    polinomio_completo = polinomio_newton # Forma completa del polinomio
    polinomio_reducido = expand(polinomio_newton) # Forma reducida del polinomio
    
    print("\nPolinomio completo:")
    print('---------------------------\n')
    print('P(x) = ', polinomio_completo)
    print("\nPolinomio reducido:")
    print('---------------------------\n')
    print('P(x) = ', polinomio_reducido)
    
    x_datos = symbols('x')
    
    expresion = polinomio_reducido
    
    pol_resultante = expresion.subs(x_datos, valor_a_interpolar)
    
    print("\nInterpolando a 0.35:")
    print('---------------------------\n')
    texto_expresion = str(expresion)
    print('P(x) = ', texto_expresion.replace('x', str(valor_a_interpolar)))
    print('---------------------------\n')
    print('P(x) = ', round(pol_resultante, 3))
    


def seleccion():
    
    opcion = input('\n¿Desea seleccionar los datos que formarán el rango de interpolación? (S, N): ').upper()
    
    if opcion == 'S':
    
        print(f"\n{'i':^8} {'x':^8} {'F(x)':^8}\n")
        
        for i, val in enumerate(valores_x):
            print(f"{i:^8} {val:^8} {valores_fx[i]:^8}")
        
        indices_seleccionados = input("\nIngresa los índices de los datos a utilizar separados por espacios: ")
        indices = list(map(int, indices_seleccionados.split()))
        x_select = [valores_x[i] for i in indices]
        fx_select = [valores_fx[i] for i in indices]
        
        x = x_select
        fx = fx_select
        
        print('\nValores a Utilizar')
        print(f"\n{'i':^8} {'x':^8} {'F(x)':^8}\n")
        for i, val in enumerate(x):
            print(f"{i:^8} {val:^8} {fx[i]:^8}")
        
        newton_base(x, fx)
        
    elif opcion == 'N':
        
        x = valores_x
        fx = valores_fx
        
        print('\nValores a Utilizar')
        print(f"\n{'i':^8} {'x':^8} {'F(x)':^8}\n")
        for i, val in enumerate(x):
            print(f"{i:^8} {val:^8} {fx[i]:^8}")
        
        newton_base(x, fx)
        
    else:
        return(seleccion())

seleccion()