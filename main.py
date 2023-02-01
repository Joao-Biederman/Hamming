from math import *
import numpy as np
import sys


if __name__ == "__main__":
    fileN = sys.argv[1]
    option = sys.argv[2]

    if(option == 'w'):
        file = open(fileN, "rb")
        file_string = file.read()
        binary_string = ""

        for char in file_string:
            data = bin(char)[2:].rjust(8, '0')
            binary_string += data

        teste = binary_string[::-1]
        bits_paridade = floor(log2(len(binary_string)))+1      

        binaryString_list = list(teste)
        
        def insertBin(binaryString, bits):
            binaryString.insert(0, "Y")
            for i in range(bits):
                pos = ceil(pow(2, i))
                binaryString.insert(pos, "X")
        

        
        insertBin(binaryString_list, bits_paridade)
        enumerate(binaryString_list)
        bits = list(enumerate(binaryString_list))
        aux = []
        for i in range(len(binaryString_list)):
            if(binaryString_list[i] == '1'):
                aux.append(i)

        Xor = 0
        for i in range(len(aux)):
            Xor = Xor ^ aux[i]

        xorBin = bin(Xor)[2:].rjust(8, '0')

        xorList = list(xorBin)
        xorList.reverse()
        bits_array = list()
        
        for i in range(len(xorList)):
            if(xorList[i] == '1'):
                if(i == 0):
                    bits_array.append(1)
                else:
                    bits_array.append(i+1)

        count = 0
        for i in range(len(binaryString_list)):
            if(binaryString_list[i] == 'X'):
                count += 1
                for j in range(len(bits_array)):
                    if(bits_array[j] == count):
                        binaryString_list[i] = 1
                if(binaryString_list[i] == 'X'):
                    binaryString_list[i] = 0
        
        stringList = list()
        stringKey = fileN + " "
        auxiliar = char
        for i in range(len(binaryString_list)):
            stringList.append(str(binaryString_list[i]))

        contador = 0
        for i in range(len(stringList)):
            if(stringList[i] == '1'):
                contador += 1

        if(contador%2 == 0):
            stringList[0] = '0'
        else:
            stringList[0] = '1'

        for i in range(len(stringList)):
            stringKey = stringKey + stringList[i]    
        print(stringKey)


        chadFile = open("chad.txt", "w")
        chadFile.write(stringKey)
        print("Hamming Efetuado!")
        print("Documento Chave Criado")
     
        file.close()
        chadFile.close()

    elif(option == 'c'):
        stringKey = ""
        file = open(fileN, "r+")
        file_stringC = file.read()
        nomeArquivo = file_stringC.rsplit( )[0]
        keyString = file_stringC.rsplit( )[1]
        listaKey = list(keyString)

        file.close()
        aux = []
        indAux = 1
        for indAux in range(len(listaKey)):
            if(listaKey[indAux] == '1'):
                aux.append(indAux)
        counter = 0
        for i in range(len(listaKey)):
            if(listaKey[i] == '1'):
                counter +=1
        
        even = bool
        if(counter%2 == 0):
            even = True
        else:
            even = False
        
        #print(binaryString_list)
        Xor = 0
        for i in range(len(aux)):
            Xor = Xor ^ aux[i]
        
        if(Xor != 0 and even == False):

            print(nomeArquivo + ": FALHOU!")
            print("AVISO: 1 soma de verificação calculada NÃO coincide")
            if(listaKey[Xor] == '0'):
                listaKey[Xor] = '1'
            elif(listaKey[Xor] == '1'):
                listaKey[Xor] = '0'
            
            for i in range(len(listaKey)):
                stringKey = stringKey + listaKey[i]    
            file = open(fileN, "w+")
            
            file.write(nomeArquivo + " " + stringKey)
            print("CORRIGINDO ERRO!")
            print("ERRO CORRIGIDO!")
            file.close()
            

        elif(Xor != 0 and even == True):
            print(nomeArquivo + ": FALHOU!")
            print("AVISO: 2 somas de verificação calculada NÃO coincide")
        
        elif(Xor == 0 and even == False):
            print(nomeArquivo + ": FALHOU!")
            print("AVISO: 1 soma de verificação calculada NÃO coincide")
            print("CORRIGINDO ERRO!")
            if(listaKey[0] == '0'):
                listaKey[0] = '1'
            if(listaKey[0] == '1'):
                listaKey[0] = '0'
            
            for i in range(len(listaKey)):
                stringKey = stringKey + listaKey[i]    
            
            file = open(fileN, "w+")
            file.write(nomeArquivo + " " + stringKey)
            print("ERRO CORRIGIDO!")
            file.close()
        
        elif(Xor == 0 and even == True):
            print(nomeArquivo + ": SUCESSO!")
            print("AVISO: Todas as somas de verificação coincidem")
        
            
            
           
        

        
        
        
        




