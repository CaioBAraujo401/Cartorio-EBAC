#include <stdio.h> // Biblioteca para fun��es de entrada e sa�da padr�o (como printf e scanf)
#include <stdlib.h> // Biblioteca para fun��es como exit() e system()
#include <locale.h> // Biblioteca para manipula��o de configura��es regionais (como setlocale)
#include <string.h> // Biblioteca para manipula��o de strings

// Fun��o para registrar os dados de um novo usu�rio
int registro() {
    char arquivo[50]; // Vari�vel para armazenar o nome do arquivo
    char cpf[40]; // Vari�vel para armazenar o CPF do usu�rio
    char nome[40]; // Vari�vel para armazenar o nome do usu�rio
    char sobrenome[40]; // Vari�vel para armazenar o sobrenome do usu�rio
    char cargo[40]; // Vari�vel para armazenar o cargo do usu�rio
    char opcao; // Vari�vel para armazenar a op��o de continuar ou voltar

    do {
        // Coleta o CPF do usu�rio
        printf("Digite o CPF a ser cadastrado: ");
        scanf("%s", cpf);  // L� o CPF informado

        // Cria um nome de arquivo com o CPF e a extens�o ".txt"
        sprintf(arquivo, "%s.txt", cpf); 
        
        // Abre o arquivo para escrita, criando-o caso n�o exista
        FILE *file = fopen(arquivo, "w");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return 1; // Se n�o conseguir abrir o arquivo, retorna erro
        }

        // Escreve o CPF no arquivo
        fprintf(file, "%s, ", cpf);
        fclose(file); // Fecha o arquivo

        // Coleta o nome do usu�rio
        printf("Digite o nome a ser cadastrado: ");
        scanf(" %[^\n]", nome); // L� o nome (incluindo espa�os)

        // Abre o arquivo para adicionar mais informa��es
        file = fopen(arquivo, "a");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return 1;
        }
        fprintf(file, "%s ", nome); // Adiciona o nome no arquivo
        fclose(file); // Fecha o arquivo

        // Coleta o sobrenome do usu�rio
        printf("Digite o sobrenome a ser cadastrado: ");
        scanf(" %[^\n]", sobrenome); // L� o sobrenome (incluindo espa�os)

        // Abre o arquivo para adicionar mais informa��es
        file = fopen(arquivo, "a");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return 1;
        }
        fprintf(file, "%s, ", sobrenome); // Adiciona o sobrenome no arquivo
        fclose(file); // Fecha o arquivo

        // Coleta o cargo do usu�rio
        printf("Digite o cargo a ser cadastrado: ");
        scanf(" %[^\n]", cargo); // L� o cargo (incluindo espa�os)

        // Abre o arquivo para adicionar mais informa��es
        file = fopen(arquivo, "a");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return 1;
        }
        fprintf(file, "%s", cargo); // Adiciona o cargo no arquivo
        fclose(file); // Fecha o arquivo

        // Pergunta se o usu�rio deseja registrar outro usu�rio
        printf("Deseja cadastrar outro usu�rio? (S para sim / N para n�o): ");
        scanf(" %c", &opcao); // L� a op��o do usu�rio
    } while (opcao == 'S' || opcao == 's'); // Se o usu�rio responder 'S', o loop continua

    system("pause"); // Pausa para o usu�rio ver a mensagem antes de continuar
    return 0; // Retorna sucesso
}

// Fun��o para consultar as informa��es de um usu�rio atrav�s do CPF
int consulta() {
    setlocale(LC_ALL, "Portuguese"); // Define o idioma e a regi�o como portugu�s

    char cpf[40]; // Vari�vel para armazenar o CPF informado pelo usu�rio
    char conteudo[200]; // Vari�vel para armazenar o conte�do lido do arquivo
    
    // Coleta o CPF do usu�rio para consulta
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf); // L� o CPF informado

    char arquivo[50]; // Vari�vel para armazenar o nome do arquivo
    sprintf(arquivo, "%s.txt", cpf); // Cria o nome do arquivo com base no CPF

    // Tenta abrir o arquivo para leitura
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Arquivo n�o localizado.\n"); // Se o arquivo n�o existir, mostra erro
        system("pause"); // Pausa a execu��o para o usu�rio ler a mensagem
        return 1; // Retorna erro
    }

    // L� o conte�do do arquivo e verifica se foi bem-sucedido
    if (fgets(conteudo, sizeof(conteudo), file) != NULL) {
        char cpf_lido[40], nome[40], sobrenome[40], cargo[100];
        
        // Divide o conte�do lido usando sscanf para separar CPF, nome, sobrenome e cargo
        sscanf(conteudo, "%[^,], %[^ ] %[^,], %[^\n]", cpf_lido, nome, sobrenome, cargo);

        // Exibe as informa��es lidas
        printf("\nEssas s�o as informa��es do usu�rio:\n");
        printf("CPF: %s\n", cpf_lido);
        printf("Nome: %s %s\n", nome, sobrenome);
        printf("Cargo: %s\n\n", cargo);
    } else {
        printf("Erro ao ler o conte�do do arquivo.\n"); // Se falhar na leitura
    }

    fclose(file); // Fecha o arquivo
    system("pause"); // Pausa para o usu�rio ver a consulta antes de continuar
    return 0; // Retorna sucesso
}

// Fun��o para sair do programa
void sair() {
    char resposta;

    // Pergunta ao usu�rio se tem certeza que deseja sair
    printf("tem certeza que deseja sair? Digite S para sair ou N para voltar ao menu: \n");
    scanf(" %c", &resposta); // L� a resposta do usu�rio (aceita letras com espa�os antes)

    // Verifica se o usu�rio deseja sair
    if (resposta == 's' || resposta == 'S') {
        exit(0); // Encerra o programa
    }
}

// Fun��o para deletar o arquivo de um usu�rio pelo CPF
int deletar() {
    setlocale(LC_ALL, "Portuguese"); // Define o idioma e a regi�o como portugu�s

    char cpf[40]; // Vari�vel para armazenar o CPF do usu�rio a ser deletado
    printf("Digite o CPF do usu�rio a ser deletado: \n");
    scanf("%s", cpf); // L� o CPF informado
    printf("Tem certeza que deseja deletar o CPF %s? \n\n", cpf);

    char resposta;
    printf("Digite 's' para confirmar ou 'n' para cancelar: ");
    scanf(" %c", &resposta);  // L� a resposta do usu�rio para confirmar a exclus�o

    if (resposta == 's' || resposta == 'S') {
        char arquivo[50]; 
        sprintf(arquivo, "%s.txt", cpf); // Cria o nome do arquivo com base no CPF
        
        // Tenta abrir o arquivo para verificar se existe
        FILE *file = fopen(arquivo, "r");

        // Verifica se o arquivo existe
        if (file == NULL) {
            printf("Arquivo n�o encontrado para o CPF %s.\n"); // Arquivo n�o encontrado
        } else {
            fclose(file); // Fecha o arquivo (n�o ser� mais necess�rio ler)

            // Tenta excluir o arquivo
            if (remove(arquivo) == 0) {
                printf("Arquivo com CPF %s foi deletado com sucesso.\n", cpf);
            } else {
                printf("Erro ao deletar o arquivo com CPF %s.\n", cpf); // Se n�o conseguir excluir
            }
        }
    } else {
        printf("Dele��o cancelada.\n"); // Caso o usu�rio cancele a exclus�o
    }

    system("pause"); // Pausa para o usu�rio ver a mensagem antes de continuar
    return 0; // Retorna sucesso
}

// Fun��o principal onde o menu � exibido e o programa � controlado
int main() {
    int opcao = 0; // Vari�vel para armazenar a op��o escolhida pelo usu�rio
    int laco = 1;

    for (laco = 1; laco == 1;) { // Loop infinito para exibir o menu
        system("cls"); // Limpa a tela do console (no Windows)
        
        setlocale(LC_ALL, "Portuguese"); // Define o idioma e a regi�o como portugu�s
        printf("--- Cart�rio da EBAC ---\n\n"); // Exibe o t�tulo do programa
        printf("Escolha a op��o desejada do menu\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n");
        printf("\t4 - Sair\n\n\n");
        printf("Op��o: "); // Solicita ao usu�rio uma op��o
        
        scanf("%d", &opcao); // L� a escolha do usu�rio
        
        system("cls"); // Limpa a tela ap�s a escolha
        
        // Executa a a��o correspondente � op��o escolhida
        switch(opcao) {
            case 1:
                registro(); // Chama a fun��o de registro
                break;
            case 2:
                consulta(); // Chama a fun��o de consulta
                break;
            case 3:
                deletar(); // Chama a fun��o de deleta��o
                break;
            case 4:
                sair(); // Chama a fun��o de sa�da
                break;
            default:
                printf("Essa op��o n�o est� dispon�vel!\n"); // Caso a op��o seja inv�lida
                system("pause"); // Pausa para o usu�rio ler a mensagem
                break;
        }
    }
}


