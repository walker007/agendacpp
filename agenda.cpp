#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

struct contato {
    char nome[32];
    char endereco[32];
    int numero;

};

void menuCli();
void menuViewBuild(int& ponteiro_opcao);
void createContato(contato* ponteiro);
void showContatos(contato* ponteiro);
int countContatos(contato* contatos);
void classificaContatos(contato* ponteiro);
int consultaBinariaContato(contato* ponteiro);
void consultaContato(contato* ponteiro);
void apagaContato(contato* ponteiro_contato);
void showContatoView(contato* ponteiro, int index);

int main()
{
    menuCli();
    return EXIT_SUCCESS;
}

void menuCli()
{
    int opcao;
    bool sair = false;
    contato *ponteiro_contatos;

    ponteiro_contatos = new contato[sizeof(contato)*20];
    for(int i =0;i<=20;i++)
    {
        strcpy(ponteiro_contatos[i].nome,"NULL");
        strcpy(ponteiro_contatos[i].endereco,"NULL");
        ponteiro_contatos[i].numero = 0;
    }

    cout <<  "--- Agenda CLI for Linux Users ---" << endl;
    cout << "Obs.: Essa agenda não persiste dados" << endl;

    while(sair == false)
    {
        int contador = countContatos(ponteiro_contatos);
        cout << "\nVocê possui " << contador << "/20 contato(s)" << endl;

        menuViewBuild(opcao);

        switch (opcao){
            case 1:
                cout << "Você Selecionou 1...\n";
                createContato(ponteiro_contatos);
                classificaContatos(ponteiro_contatos);
            break;
            case 2:
                cout << "Você Selecionou 2...\n";
                classificaContatos(ponteiro_contatos);
                showContatos(ponteiro_contatos);
            break;
            case 3:
                cout << "Você Selecionou 3...\n";
                consultaContato(ponteiro_contatos);
            break;
            case 4:
                cout << "Você selecionou 4...\n";
                apagaContato(ponteiro_contatos);
                classificaContatos(ponteiro_contatos);
            break;
            default:
                cout << "Você selecionou S..."<< endl;
                sair = true;
            break;
        }

     opcao = 0;

    }
}

void menuViewBuild(int& ponteiro_opcao)
{

    cout << "\nBem vindo à Agenda CLI..."<< endl;
    cout << "Selecione uma das opções a Seguir: \n";
    cout << "[1] Cadastrar um novo contato \n";
    cout << "[2] Exibir Contatos \n";
    cout << "[3] Pesquisa contato por nome \n";
    cout << "[4] Apagar Contato \n";
    cout << "[S] Sair...\n";
    cout << "Digite uma opção entre as que aparecem na tela e aperte [Enter]: ";
    cin >> ponteiro_opcao;
    cin.ignore(8, '\n');

}

void createContato(contato* ponteiro)
{

    int indice = 0, contador = countContatos(ponteiro);
    if(contador == 20)
    {
        cout << "Você já atingiu a Cota de contatos, \npara cadastrar mais exclua alguns contatos\n";
        return;
    }

   for(int i =0; i<=20;i++)
   {

       if(strcmp(ponteiro[i].nome, "NULL") == 0)
       {
           indice = i;
           break;

       }

   }

   char numerochar[11], nome[32], endereco[32];

    cout << "Informe o nome: " ;
    cin.getline(nome, sizeof(nome));
    strcpy(ponteiro[indice].nome, nome);

    cout << "Informe o Endereço: " ;
    cin.getline(endereco, sizeof(endereco));
    strcpy(ponteiro[indice].endereco, endereco);

    cout << "Informe o numero: " ;
    cin.getline(numerochar, sizeof(numerochar));
    ponteiro[indice].numero = atoi(numerochar);

    cout << "Salvando Contato..." << endl ;

}

int countContatos(contato* contatos)
{
    int contagem = 0;

    for(int i=0;i<=20;i++)
    {
        if(strcmp(contatos[i].nome, "NULL") != 0)
        {
            contagem++;
        }
    }

    return contagem;
}

void classificaContatos(contato* ponteiro)
{
    contato contato_auxiliar;
    int i,j, contador;

    contador = countContatos(ponteiro);

    for(i=0;i<=contador;i++)
    {

        for(j=0;j<=contador;j++)
        {

            if(strcmp(ponteiro[i].nome, ponteiro[j].nome) < 0 and !(strcmp(ponteiro[i].nome,"NULL") == 0))
            {
                contato_auxiliar = ponteiro[i];
                ponteiro[i] = ponteiro[j];
                ponteiro[j] = contato_auxiliar;
            }

        }
    }
}

void showContatos(contato* ponteiro)
{
    int contador = countContatos(ponteiro);

    for(int i =0; i<=20;i++)
    {
        if(strcmp(ponteiro[i].nome, "NULL") != 0)
        {
            showContatoView(ponteiro, i);
        }
    }

    if(contador < 1)
    {
        cout << "Você não possui contatos a serem exibidos..." << endl;
    }

    cout << "[Enter] Para Voltar ao Menu...";
    cin.get();
    cout << "Retornando...";
}

void consultaContato(contato* ponteiro)
{
   int contato = consultaBinariaContato(ponteiro);
   
    if(contato >= 0)
    {
        showContatoView(ponteiro, contato);
    }else{
        cout << "O contato que você consultou não Existe..." << endl;
    }

}

void apagaContato(contato* ponteiro_contato)
{
    char resposta[1];
    int contato;

    contato = consultaBinariaContato(ponteiro_contato);
    
    cout << "Tem certeza que deseja apagar o contato? " << endl;

    showContatoView(ponteiro_contato, contato);
            
    cout << "[S] para confirmar ou [N] para retornar: ";
    cin >> resposta;

    if(islower(resposta[0]) and (strcmp(resposta, "s") == 0) or isupper(resposta[0]) and (strcmp(resposta, "S") == 0))
    {
        strcpy(ponteiro_contato[contato].nome,"NULL");
        strcpy(ponteiro_contato[contato].endereco,"NULL");
        ponteiro_contato[contato].numero = 0;
    }
}

int consultaBinariaContato(contato* ponteiro)
{
    char consulta[32];
    int inicio = 0 , fim = countContatos(ponteiro)-1 , meio = (inicio+fim)/2;

    cout << "Consulta de contato por nome..." << "\nForneça um nome para consulta: ";
    cin.getline(consulta, sizeof(consulta));

    while(strcmp(consulta, ponteiro[meio].nome) != 0 && meio != fim)
    {
      meio =(inicio+fim)/2;

      if(strcmp(consulta, ponteiro[meio].nome) > 0)
      {

        inicio = meio+1;

      }else{

        fim=meio;
        meio=(inicio+fim)/2;

      }
    }

    if(strcmp(consulta, ponteiro[meio].nome) == 0)
    {
       return meio;
    }
    
    return -1;
}

void showContatoView(contato* ponteiro, int index)
{
    cout << "-----------------------------------" << endl;
    cout << "Codigo: " << index+1 << endl;
    cout << "Nome: " << ponteiro[index].nome << endl;
    cout << "Endereço: " << ponteiro[index].endereco << endl;
    cout << "Número: " << ponteiro[index].numero << endl;
}