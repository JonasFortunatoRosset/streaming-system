#include <iostream>
#include <locale.h>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
#include <sstream>

using namespace std;

// Classe para definir usuários
class UsuarioModel{
	private:
		unsigned int id_;
		string nome_;
		string senha_;
		vector<int> inscricoes_;
		string tipo_;
	public:
		UsuarioModel(int id, string nome, string senha, string tipo);
		
};

// Classe para definir vídeo
class VideoModel{
	private:
		unsigned int id_;
		string nome_;
		string duracao_;
		string qualidade_;
		string categoria_;
		string tipo_;
		
	public:
		VideoModel(int id, string nome, string duracao, string qualidade, string categoria, string tipo);
};

// Classe para definir histórico (associação entre o usuário e o vídeo assistido)
class HistoricoModel{
	private:
		int id_video_;
		int id_usuario_;
	public:
		HistoricoModel(int id_video, int id_usuario);
};

// Classe para definir plano
class PlanoModel{
	private:
		unsigned int id_;
		string nome_;
		float preco_;
		string data_expiracao_;
		int id_usuario_;
	
	public:
		PlanoModel(int id, string nome, float preco, string data_expiracao, int id_usuario);
};

// Função sem retorno para cadastro de novo usuário
void cadastrarUsuario(vector<UsuarioModel> &lista_de_usuarios){
	unsigned int id = lista_de_usuarios.size();
	string nome;
	string senha;
	string tipo;
	bool estado = false;
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Digite o seu nome: ";
	getline(cin, nome);
	cout << "Digite um senha forte: ";
	getline(cin, senha);
	while (estado != true){
		if (senha.size() < 8){
			cout << "Digite um senha com mais de  caracteres: ";
			getline(cin, senha);
		}
		else {
			estado = true;
		}
	}
	cout << "Escolha o tipo da sua conta: \n 1 - Usuário comum \n 2 - Anunciante";
	cin >> tipo;
	UsuarioModel usuario_model(id, nome, senha, tipo);
	lista_de_usuarios.push_back(usuario_model);
}

// Função sem retorno para cadastro de novo vídeo
void cadastrarVideo(vector<VideoModel> &lista_de_videos){
	unsigned int id = lista_de_videos.size();
	string nome;
	string duracao;
	string qualidade;
	string categoria;
	string tipo;
	int opcao = 0;
	bool estado = false;
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Digite o nome do vídeo: ";
	getline(cin, nome);
	cout << "Digite a duração do vídeo: ";
	getline(cin, duracao);
	while (estado != true){
		cout << "Selecione detre as opções a qualidade do vídeo: \n 1 - 2160p \n 2 - 1440p \n 3 - 1080p";
		cin >> opcao;
		
		switch(opcao){
			case 1:
				qualidade = "2160p";
				estado = true;
				break;
			case 2:
				qualidade = "1440p";
				estado = true;
				break;
			case 3:
				qualidade = "1080p";
				estado = true;
				break;
			default:
				break;
		}
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Digite a categoria do vídeo";
	getline(cin, categoria);
	cout << "Digite o tipo do vídeo";
	getline(cin, tipo);
	
	VideoModel video_model(id, nome, duracao, qualidade, categoria, tipo);
	lista_de_videos.push_back(video_model);
}

// Função sem retorno para cadastro de novo plano
void cadastrarPlano(vector<PlanoModel> &lista_de_planos){
	unsigned int id = lista_de_planos.size();
	string nome;
	float preco;
	string data_expiracao;
	unsigned int id_usuario;
	bool estado = false;
	int opcao = 0;
	
	while (estado != true) {
		cout << "Escolha seu plano \n 1 - Plano com anúncios"
							   	  "\n 2 - Plano sem anúncios"
							      "\n 3 - Plano Anunciante"
							      "\n 4 - Plano Kids";
		cin >> opcao;
		
		switch(opcao){
			case 1:
				nome = "Plano com anúncios";
				preco = 12.99;
				estado = true;
				break;
			case 2:
				nome = "Plano sem anúncios";
				preco = 21.90;
				estado = true;
				break;
			case 3:
				nome = "Plano Premium";
				estado = true;
				preco = 30.99;
				break;
			case 4:
				nome = "Plano Kids";
				preco = 39.99;
				estado = true;
				break;
			default:
				break;
		}
	}
	time_t t = time(0);
	tm* now = localtime(&t);
	int dia =  now->tm_mday;
	int mes = now->tm_mon + 1;
	int ano = now->tm_year + 1900;
	
	int calendario_31dias[7] = {1, 3, 5, 7, 8, 10, 12}; // Meses com 31 dias
	int calendario_30dias[4] = {4, 6, 9, 11};
	stringstream diass;
	stringstream mess;
	stringstream anoss;
	
	for (int i = 0; i < 7; ++i){ // Verifica meses com 31 dias para e no dia 1 para somar apenas na variável "dia" os dias para expiração do plano
		if (((dia == 1) || (dia == 2)) && (calendario_31dias[i] == mes)){ // Se dia do mês for 1 ou 2 em meses de 31 dias
			dia += 29;
			diass << dia; // string stream --> dia(ss)
			mess << mes;
			anoss << ano;
			data_expiracao = diass.str() + mess.str() + anoss.str();
		}
		else if (calendario_31dias[i] == mes){ // Se mês não for de 31 dias e diferente do mes 1 e 2 - faz incremento para dias !(1 e 2)
			dia -= 2;
			mes += 1;
			diass << dia;
			mess << mes;
			anoss << ano;
			data_expiracao = diass.str() + mess.str() + anoss.str();
		}
		if ((mes == 2) && (dia == 29)){ // Redefine os valores que cairam na condição da linha 192 - (mudança de mes 1 e dia 31) - Correção para ano não bissexto
			dia = 1;
			mes += 1;
			diass << dia;
			mess << mes;
			anoss << ano;
			data_expiracao = diass.str() + mess.str() + anoss.str();
		}
	}
	
	for (int j = 0; j < 4; ++j){ 
		if (calendario_30dias[j] == mes){
			dia -= 1;
			mes += 1;
			diass << dia;
			mess << mes;
			anoss << ano;
			data_expiracao = diass.str() + mess.str() + anoss.str();
		}
		else if ((dia == 1) && (calendario_30dias[j] == mes)){
			dia += 29;
			diass << dia;
			mess << mes;
			anoss << ano;
			data_expiracao = diass.str() + mess.str() + anoss.str();
		}
	}
	
	if ((mes == 2) && (dia == 29)){ // Quando é dia 29 de ano bissexto
			mes += 1;
			diass << dia;
			mess << mes;
			anoss << ano;
			data_expiracao = diass.str() + mess.str() + anoss.str();
		}
	// else if para mes == 2 em ano bissexto --- mes += 1
    else if (mes == 2){ // Verifica para fevereiro e adiciona o valor dos dias do plano e incrementa 1 ao mês
		dia += 1;
		mes += 1;
		diass << dia;
		mess << mes;
		anoss << ano;
		data_expiracao = diass.str() + mess.str() + anoss.str();
	}
	else if (mes == 13){
		mes = 1;
		ano += 1;
		diass << dia;
		mess << mes;
		anoss << ano;
		data_expiracao = diass.str() + mess.str() + anoss.str();
	}
	
	cout << "Digite seu id de usuário: ";
	cin >> id_usuario;
	
	PlanoModel plano_model(id, nome, preco, data_expiracao, id_usuario);
	lista_de_planos.push_back(plano_model);
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    bool op = false;
    vector<UsuarioModel> lista_de_usuarios;
    vector<VideoModel> lista_de_videos;
    vector<PlanoModel> lista_de_planos;
    
    while (op != true){
    	int opcao = 0;
        const string menu = " 1 - Cadastrar usuário" 
                            "\n 2 - Cadastrar vídeo" 
                            "\n 3 - Cadastrar plano"
                            "\n 4 - Assistir vídeo"
                            "\n 5 - Entrar em minha conta" // caso para criador de conteúdo ou apenas usuario -- opcao de se inscrever
                            "\n 6 - Inscrever-se em um canal" // Obriga a entrar na conta para se inscrever
                            "\n 7 - Sair "
							"\n Responda: ";
        cout << menu;
        cin >> opcao;
        
        if (opcao == 1){
        	cadastrarUsuario(lista_de_usuarios);
		}
		else if (opcao == 2){
			cadastrarVideo(lista_de_videos);
		}
		else if (opcao == 3){
			cadastrarPlano(lista_de_planos);
		}
		else {
			op = true;
		}
    }

    return 0;
}

HistoricoModel::HistoricoModel(int id_video, int id_usuario):
	id_video_(id_video), id_usuario_(id_usuario){}
UsuarioModel::UsuarioModel(int id, string nome, string senha, string tipo):
	id_(id), nome_(nome), senha_(senha), tipo_(tipo){}
VideoModel::VideoModel(int id, string nome, string duracao, string qualidade, string categoria, string tipo):
	id_(id), nome_(nome), duracao_(duracao), qualidade_(qualidade), categoria_(categoria), tipo_(tipo){}
PlanoModel::PlanoModel(int id, string nome, float preco, string data_expiracao, int id_usuario):
	id_(id), nome_(nome), preco_(preco), data_expiracao_(data_expiracao), id_usuario_(id_usuario){}
