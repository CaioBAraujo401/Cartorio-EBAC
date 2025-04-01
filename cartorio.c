#include <stdio.h> // Biblioteca para funções de entrada e saída padrão (como printf e scanf)
#include <stdlib.h> // Biblioteca para funções como exit() e system()
#include <locale.h> // Biblioteca para manipulação de configurações regionais (como setlocale)
#include <string.h> // Biblioteca para manipulação de strings

// Função para registrar os dados de um novo usuário
int registro() {
    char arquivo[50]; // Variável para armazenar o nome do arquivo
    char cpf[40]; // Variável para armazenar o CPF do usuário
    char nome[40]; // Variável para armazenar o nome do usuário
    char sobrenome[40]; // Variável para armazenar o sobrenome do usuário
    char cargo[40]; // Variável para armazenar o cargo do usuário
    char opcao; // Variável para armazenar a opção de continuar ou voltar

    do {
        // Coleta o CPF do usuário
        printf("Digite o CPF a ser cadastrado: ");
        scanf("%s", cpf);  // Lê o CPF informado

        // Cria um nome de arquivo com o CPF e a extensão ".txt"
        sprintf(arquivo, "%s.txt", cpf); 
        
        // Abre o arquivo para escrita, criando-o caso não exista
        FILE *file = fopen(arquivo, "w");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return 1; // Se não conseguir abrir o arquivo, retorna erro
        }

        // Escreve o CPF no arquivo
        fprintf(file, "%s, ", cpf);
        fclose(file); // Fecha o arquivo

        // Coleta o nome do usuário
        printf("Digite o nome a ser cadastrado: ");
        scanf(" %[^\n]", nome); // Lê o nome (incluindo espaços)

        // Abre o arquivo para adicionar mais informações
        file = fopen(arquivo, "a");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return 1;
        }
        fprintf(file, "%s ", nome); // Adiciona o nome no arquivo
        fclose(file); // Fecha o arquivo

        // Coleta o sobrenome do usuário
        printf("Digite o sobrenome a ser cadastrado: ");
        scanf(" %[^\n]", sobrenome); // Lê o sobrenome (incluindo espaços)

        // Abre o arquivo para adicionar mais informações
        file = fopen(arquivo, "a");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return 1;
        }
        fprintf(file, "%s, ", sobrenome); // Adiciona o sobrenome no arquivo
        fclose(file); // Fecha o arquivo

        // Coleta o cargo do usuário
        printf("Digite o cargo a ser cadastrado: ");
        scanf(" %[^\n]", cargo); // Lê o cargo (incluindo espaços)

        // Abre o arquivo para adicionar mais informações
        file = fopen(arquivo, "a");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return 1;
        }
        fprintf(file, "%s", cargo); // Adiciona o cargo no arquivo
        fclose(file); // Fecha o arquivo

        // Pergunta se o usuário deseja registrar outro usuário
        printf("Deseja cadastrar outro usuário? (S para sim / N para não): ");
        scanf(" %c", &opcao); // Lê a opção do usuário
    } while (opcao == 'S' || opcao == 's'); // Se o usuário responder 'S', o loop continua

    system("pause"); // Pausa para o usuário ver a mensagem antes de continuar
    return 0; // Retorna sucesso
}

// Função para consultar as informações de um usuário através do CPF
int consulta() {
    setlocale(LC_ALL, "Portuguese"); // Define o idioma e a região como português

    char cpf[40]; // Variável para armazenar o CPF informado pelo usuário
    char conteudo[200]; // Variável para armazenar o conteúdo lido do arquivo
    
    // Coleta o CPF do usuário para consulta
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf); // Lê o CPF informado

    char arquivo[50]; // Variável para armazenar o nome do arquivo
    sprintf(arquivo, "%s.txt", cpf); // Cria o nome do arquivo com base no CPF

    // Tenta abrir o arquivo para leitura
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Arquivo não localizado.\n"); // Se o arquivo não existir, mostra erro
        system("pause"); // Pausa a execução para o usuário ler a mensagem
        return 1; // Retorna erro
    }

    // Lê o conteúdo do arquivo e verifica se foi bem-sucedido
    if (fgets(conteudo, sizeof(conteudo), file) != NULL) {
        char cpf_lido[40], nome[40], sobrenome[40], cargo[100];
        
        // Divide o conteúdo lido usando sscanf para separar CPF, nome, sobrenome e cargo
        sscanf(conteudo, "%[^,], %[^ ] %[^,], %[^\n]", cpf_lido, nome, sobrenome, cargo);

        // Exibe as informações lidas
        printf("\nEssas são as informações do usuário:\n");
        printf("CPF: %s\n", cpf_lido);
        printf("Nome: %s %s\n", nome, sobrenome);
        printf("Cargo: %s\n\n", cargo);
    } else {
        printf("Erro ao ler o conteúdo do arquivo.\n"); // Se falhar na leitura
    }

    fclose(file); // Fecha o arquivo
    system("pause"); // Pausa para o usuário ver a consulta antes de continuar
    return 0; // Retorna sucesso
}

// Função para sair do programa
void sair() {
    char resposta;

    // Pergunta ao usuário se tem certeza que deseja sair
    printf("tem certeza que deseja sair? Digite S para sair ou N para voltar ao menu: \n");
    scanf(" %c", &resposta); // Lê a resposta do usuário (aceita letras com espaços antes)

    // Verifica se o usuário deseja sair
    if (resposta == 's' || resposta == 'S') {
        exit(0); // Encerra o programa
    }
}

// Função para deletar o arquivo de um usuário pelo CPF
int deletar() {
    setlocale(LC_ALL, "Portuguese"); // Define o idioma e a região como português

    char cpf[40]; // Variável para armazenar o CPF do usuário a ser deletado
    printf("Digite o CPF do usuário a ser deletado: \n");
    scanf("%s", cpf); // Lê o CPF informado
    printf("Tem certeza que deseja deletar o CPF %s? \n\n", cpf);

    char resposta;
    printf("Digite 's' para confirmar ou 'n' para cancelar: ");
    scanf(" %c", &resposta);  // Lê a resposta do usuário para confirmar a exclusão

    if (resposta == 's' || resposta == 'S') {
        char arquivo[50]; 
        sprintf(arquivo, "%s.txt", cpf); // Cria o nome do arquivo com base no CPF
        
        // Tenta abrir o arquivo para verificar se existe
        FILE *file = fopen(arquivo, "r");

        // Verifica se o arquivo existe
        if (file == NULL) {
            printf("Arquivo não encontrado para o CPF %s.\n"); // Arquivo não encontrado
        } else {
            fclose(file); // Fecha o arquivo (não será mais necessário ler)

            // Tenta excluir o arquivo
            if (remove(arquivo) == 0) {
                printf("Arquivo com CPF %s foi deletado com sucesso.\n", cpf);
            } else {
                printf("Erro ao deletar o arquivo com CPF %s.\n", cpf); // Se não conseguir excluir
            }
        }
    } else {
        printf("Deleção cancelada.\n"); // Caso o usuário cancele a exclusão
    }

    system("pause"); // Pausa para o usuário ver a mensagem antes de continuar
    return 0; // Retorna sucesso
}

// Função principal onde o menu é exibido e o programa é controlado
int main() {
    int opcao = 0; // Variável para armazenar a opção escolhida pelo usuário
    int laco = 1;

    for (laco = 1; laco == 1;) { // Loop infinito para exibir o menu
        system("cls"); // Limpa a tela do console (no Windows)
        
        setlocale(LC_ALL, "Portuguese"); // Define o idioma e a região como português
        printf("--- Cartório da EBAC ---\n\n"); // Exibe o título do programa
        printf("Escolha a opção desejada do menu\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n");
        printf("\t4 - Sair\n\n\n");
        printf("Opção: "); // Solicita ao usuário uma opção
        
        scanf("%d", &opcao); // Lê a escolha do usuário
        
        system("cls"); // Limpa a tela após a escolha
        
        // Executa a ação correspondente à opção escolhida
        switch(opcao) {
            case 1:
                registro(); // Chama a função de registro
                break;
            case 2:
                consulta(); // Chama a função de consulta
                break;
            case 3:
                deletar(); // Chama a função de deletação
                break;
            case 4:
                sair(); // Chama a função de saída
                break;
            default:
                printf("Essa opção não está disponível!\n"); // Caso a opção seja inválida
                system("pause"); // Pausa para o usuário ler a mensagem
                break;
        }
    }
}


