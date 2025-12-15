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
		string tipo_;
	public:
		vector<int> inscricoes;
		
		UsuarioModel(int id, string nome, string senha, string tipo);
		
		string pegaNome(){
			return nome_;
		}
		
		string pegaSenha(){
			return senha_;
		}
		
		int pegaId(){
			return id_;
		}
		
		void inscreve(int id_canal){
			inscricoes.push_back(id_canal);
		}
		
		
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
		int id_usuario_;
		
	public:
		VideoModel(int id, string nome, string duracao, string qualidade, string categoria, string tipo, int id_usuario);
		
		string pegaNome(){
			return nome_;
		}
		
		string pegaDuracao(){
			return duracao_;
		}
		
		string pegaQualidade(){
			return qualidade_;
		}
		
		string pegaCategoria(){
			return categoria_;
		}
		
		string pegaTipo(){
			return tipo_;
		}
		
		int pegaId(){
			return id_;
		}
		
		int pegaIdUsu(){
			return id_usuario_;
		}
};

// Classe para definir histórico (associação entre o usuário e o vídeo assistido)
class HistoricoModel{
	private:
		int id_video_;
		int id_usuario_;
	public:
		HistoricoModel(int id_video, int id_usuario);
		
		int pegaIdVideo(){
			return id_video_;
		}
		
		int pegaIdUsu(){
			return id_usuario_;
		};
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
		
		string pegaNome(){
			return nome_;
		}
		
		float pegaPreco(){
			return preco_;
		}
		
		string pegaData(){
			return data_expiracao_;
		}
		
		int pegaIdUsu(){
			return id_usuario_;
		}
};

// Função sem retorno para cadastro de novo usuário
void cadastrarUsuario(vector<UsuarioModel> &lista_de_usuarios){
	unsigned int id = lista_de_usuarios.size();
	string nome;
	string senha;
	string tipo;
	bool estado = false;
	bool usuario_invalido = false;
	
	cout << "Digite o seu nome: ";
	getline(cin, nome);
	
	for(int i=0; i < lista_de_usuarios.size(); i++){
		if(nome == lista_de_usuarios[i].pegaNome()){
			usuario_invalido = true;
		}
	}
	if(usuario_invalido == true){
		cout<<"Nome de usuário já registrado"<<endl;
		cout<<endl;
	}
	else{
	
	cout << "Digite uma senha forte: ";
	getline(cin, senha);
	while (estado != true){
		if (senha.size() < 8){
			cout << "Digite uma senha com mais de 8 caracteres: ";
			getline(cin, senha);
		}
		else {
			estado = true;
		}
	}
	cout << "Escolha o tipo da sua conta: \n 1 - Usuário comum \n 2 - Anunciante \n Responda: ";
	cin >> tipo;
	UsuarioModel usuario_model(id, nome, senha, tipo);
	lista_de_usuarios.push_back(usuario_model);
    }
}

// Função sem retorno para cadastro de novo vídeo
void cadastrarVideo(vector<VideoModel> &lista_de_videos, int id_usuario){
	unsigned int id = lista_de_videos.size();
	string nome;
	string duracao;
	string qualidade;
	string categoria;
	string tipo;
	int opcao = 0;
	bool estado = false;
	
	cin.ignore();
	cout << "Digite o nome do vídeo: ";
	getline(cin, nome);
	cout << "Digite a duração do vídeo: ";
	getline(cin, duracao);
	while (estado != true){
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Selecione dentre as opções a qualidade do vídeo: \n 1 - 2160p \n 2 - 1440p \n 3 - 1080p \n Responda: ";
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
	cin.ignore();
	cout << "Digite a categoria do vídeo: ";
	getline(cin, categoria);
	cout << "Digite o tipo do vídeo: ";
	getline(cin, tipo);
	
	VideoModel video_model(id, nome, duracao, qualidade, categoria, tipo, id_usuario);
	lista_de_videos.push_back(video_model);
}

// Função sem retorno para cadastro de novo plano
void cadastrarPlano(vector<PlanoModel> &lista_de_planos, int id_usuario){
	unsigned int id = lista_de_planos.size();
	string nome;
	float preco;
	string data_expiracao;
	bool estado = false;
	int opcao = 0;
	
	while (estado != true) {
		cout << "Escolha seu plano \n 1 - Plano com anúncios"
							   	  "\n 2 - Plano sem anúncios"
							      "\n 3 - Plano Premium"
							      "\n 4 - Plano Kids"
								  "\n Responda: ";
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
			data_expiracao = diass.str() + "/" +mess.str() + "/"+ anoss.str();
		}
		else if (calendario_31dias[i] == mes){ // Se mês não for de 31 dias e diferente do mes 1 e 2 - faz incremento para dias !(1 e 2)
			dia -= 2;
			mes += 1;
			diass << dia;
			mess << mes;
			anoss << ano;
			data_expiracao = diass.str() + "/" +mess.str() + "/"+ anoss.str();
		}
		if ((mes == 2) && (dia == 29)){ // Redefine os valores que cairam na condição da linha 192 - (mudança de mes 1 e dia 31) - Correção para ano não bissexto
			dia = 1;
			mes += 1;
			diass << dia;
			mess << mes;
			anoss << ano;
			data_expiracao = diass.str() + "/" +mess.str() + "/"+ anoss.str();
		}
	}
	
	for (int j = 0; j < 4; ++j){ 
		if (calendario_30dias[j] == mes){
			dia -= 1;
			mes += 1;
			diass.str("");
			diass.clear();
			diass << dia;
			
			mess.str("");
			mess.clear();
			mess << mes;
			
			anoss.str("");
			anoss.clear();
			anoss << ano;
			
			data_expiracao = diass.str() + "/" +mess.str() + "/"+ anoss.str();
		}
		else if ((dia == 1) && (calendario_30dias[j] == mes)){
			dia += 29;
			diass.str("");
			diass.clear();
			diass << dia;
			
			mess.str("");
			mess.clear();
			mess << mes;
			
			anoss.str("");
			anoss.clear();
			anoss << ano;
			data_expiracao = diass.str() + "/" +mess.str() + "/"+ anoss.str();
		}
	}
	
	if ((mes == 2) && (dia == 29)){ // Quando é dia 29 de ano bissexto
			mes += 1;
			diass.str("");
			diass.clear();
			diass << dia;
			
			mess.str("");
			mess.clear();
			mess << mes;
			
			anoss.str("");
			anoss.clear();
			anoss << ano;
			data_expiracao = diass.str() + "/" +mess.str() + "/"+ anoss.str();
		}
	// else if para mes == 2 em ano bissexto --- mes += 1
    else if (mes == 2){ // Verifica para fevereiro e adiciona o valor dos dias do plano e incrementa 1 ao mês
		dia += 1;
		mes += 1;
			diass.str("");
			diass.clear();
			diass << dia;
			
			mess.str("");
			mess.clear();
			mess << mes;
			
			anoss.str("");
			anoss.clear();
			anoss << ano;
		data_expiracao = diass.str() + "/" +mess.str() + "/"+ anoss.str();
	}
	else if (mes == 13){
		mes = 1;
		ano += 1;
			diass.str("");
			diass.clear();
			diass << dia;
			
			mess.str("");
			mess.clear();
			mess << mes;
			
			anoss.str("");
			anoss.clear();
			anoss << ano;
		data_expiracao = diass.str() + "/" +mess.str() + "/"+ anoss.str();
	}
	
	PlanoModel plano_model(id, nome, preco, data_expiracao, id_usuario);
	lista_de_planos.push_back(plano_model);
}

bool op = false;
bool logoff = false;
bool ja_inscrito = false;
vector<UsuarioModel> lista_de_usuarios;
vector<VideoModel> lista_de_videos;
vector<PlanoModel> lista_de_planos;
vector<HistoricoModel>historico;
string nome_da_conta;
string senha_da_conta;
int op_video = 0;
int op_canal = 0;



//Função chama menu do usuario
void menuUsuario(int id_usuario, vector<VideoModel> &lista_de_videos, vector<PlanoModel> &lista_de_planos){
	
	
    while (op != true){
    	ja_inscrito = false;
    	int inscritos = 0;
    	int views = 0;
    	int opcao = 0;
        const string menu = " 1 - Cadastrar vídeo" 
                            "\n 2 - Meus vídeos"
							"\n 3 - Cadastrar plano"
							"\n 4 - Meus Planos"
							"\n 5 - Assistir vídeo"
							"\n 6 - Histórico"
                            "\n 7 - Inscrever-se em um canal" 
                            "\n 8 - Inscrições"
                            "\n 9 - Sair "
							"\n Responda: ";
        cout << menu;
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
		if (opcao == 1){ // Cadastrar vídeo
			cadastrarVideo(lista_de_videos, id_usuario);
		}
		else if(opcao == 2){ // Meus vídeos
			for(int j=0; j < lista_de_videos.size(); j++){
			views = 0;
			if(lista_de_videos[j].pegaIdUsu() == id_usuario){
				for(int i=0; i < historico.size(); i++){
					if(historico[i].pegaIdVideo() == lista_de_videos[j].pegaId()){
						views+=1;
					}
				}
			cout<<lista_de_videos[j].pegaNome()<<" - "<<lista_de_videos[j].pegaDuracao()<<" min"<<" - "<<lista_de_videos[j].pegaQualidade()<<" - "<<lista_de_videos[j].pegaCategoria()<<" - "<<lista_de_videos[j].pegaTipo()<<" - "<<views<<" visualizações"<<endl;
			cout<<endl;
			}
		  }
		}
		else if (opcao == 3){ // Cadastrar planos
			cadastrarPlano(lista_de_planos, id_usuario);
		}
		else if(opcao == 4){ // Meus planos
			for(int i=0; i < lista_de_planos.size(); i++){
				if(lista_de_planos[i].pegaIdUsu() == id_usuario){
					cout<<lista_de_planos[i].pegaNome()<<" - "<<lista_de_planos[i].pegaPreco()<<" - "<<lista_de_planos[i].pegaData()<<endl;
					cout<<endl;
				}
			}
		}
		
		else if(opcao == 5){ // Assistir vídeos
			
			for(int j=0; j < lista_de_videos.size(); j++){
			views = 0;
				for(int i=0; i < historico.size(); i++){
					if(historico[i].pegaIdVideo() == lista_de_videos[j].pegaId()){
						views+=1;
					}
				}
			cout<<"("<<lista_de_videos[j].pegaId()<<")"<<" - "<<lista_de_videos[j].pegaNome()<<" - "<<lista_de_videos[j].pegaDuracao()<<" min"<<" - "<<lista_de_videos[j].pegaQualidade()<<" - "<<lista_de_videos[j].pegaCategoria()<<" - "<<lista_de_videos[j].pegaTipo()<<" - "<<views<<" visualizações"<<endl;
			cout<<endl;			
			}
			
			cout<<"Digite o id do video que deseja assitir: "<<endl;
			cin>>op_video;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			HistoricoModel historico_model(op_video, id_usuario);
			historico.push_back(historico_model);
			
		}
		
		else if(opcao == 6){ // Histórico dos vídeos vistos pelo usuário e lógica para somar as views
			
				for(int i=0; i < historico.size(); i++){
					if(historico[i].pegaIdUsu() == id_usuario){
						for(int j=0; j < lista_de_videos.size(); j++){
							views = 0;
							if(historico[i].pegaIdVideo() == lista_de_videos[j].pegaId()){
								for(int v=0; v < historico.size(); v++){
									if(historico[v].pegaIdVideo() == lista_de_videos[j].pegaId()){
									views+=1;
								}								
							}
							cout<<"("<<lista_de_videos[j].pegaId()<<")"<<" - "<<lista_de_videos[j].pegaNome()<<" - "<<lista_de_videos[j].pegaDuracao()<<" min"<<" - "<<lista_de_videos[j].pegaQualidade()<<" - "<<lista_de_videos[j].pegaCategoria()<<" - "<<lista_de_videos[j].pegaTipo()<<" - "<<views<<" visualizações"<<endl;
							cout<<endl;	
						}
					}
				}
			}
		}
	
		else if(opcao == 7){ // Inscrever-se em um canal
			for(int i=0; i < lista_de_usuarios.size(); i++){
				inscritos = 0;
				//conta a quantidade de inscritos
				for(int l=0; l < lista_de_usuarios.size(); l++){
					for(int j=0; j < lista_de_usuarios[l].inscricoes.size(); j++){	
						if(lista_de_usuarios[l].inscricoes[j] == lista_de_usuarios[i].pegaId()){
							inscritos+=1;
						}
					}
				}
				cout<<"("<<lista_de_usuarios[i].pegaId()<<")"<<" - "<<lista_de_usuarios[i].pegaNome()<<" - "<<inscritos<<" inscritos"<<endl;
				cout<<endl;
			}
			cout<<"Digite o id do canal ao qual deseja se inscrever: "<<endl;
			cin >> op_canal;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			if(op_canal != id_usuario){
			for(int k=0; k < lista_de_usuarios.size(); k++){
				if(lista_de_usuarios[k].pegaId() == id_usuario){
					for(int c=0; c < lista_de_usuarios[k].inscricoes.size(); c++){
						if(lista_de_usuarios[k].inscricoes[c] == op_canal){
							ja_inscrito = true;
						}
					}
					if(ja_inscrito == false){
					
					lista_de_usuarios[k].inscricoes.push_back(op_canal);
					}
					else{
						cout<<endl;
						cout<<"Já inscrito"<<endl;
						cout<<endl;
					}
					}

				}

			}
			else{
				cout<<endl;
				cout<<"Ação não permitida"<<endl;
				cout<<endl;
			}
			
		}
		
		else if(opcao == 8){ // Inscricoes
			for(int i=0; i < lista_de_usuarios.size(); i++){
				if(lista_de_usuarios[i].pegaId() == id_usuario){ // encontra usuario logado / i
					for(int j=0; j < lista_de_usuarios[i].inscricoes.size(); j++){//percorre inscricoes do usuario logado  / j
						for(int l=0; l < lista_de_usuarios.size(); l++){
							if(lista_de_usuarios[l].pegaId() == lista_de_usuarios[i].inscricoes[j]){//se encontrar um usuario correspondente a j / l
							   inscritos = 0;
								
								for(int k=0; k < lista_de_usuarios.size(); k++){ //percorre 
									for(int u=0; u < lista_de_usuarios[k].inscricoes.size(); u++){	
										if(lista_de_usuarios[k].inscricoes[u] == lista_de_usuarios[l].pegaId()){
											inscritos+=1;
										}
									}
								}								
								cout<<lista_de_usuarios[l].pegaNome()<<" - "<<inscritos<<" inscritos"<<endl;
								cout<<endl;
							}
						}
					}
				}
			}
		}
		else { // Sair
			op = true;
		}
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    
    while (logoff != true){
    	op = false;
    	int opcao = 0;
    	const string menu = " 1 - Logar usuário"
    						"\n 2 - Cadastrar usuário"
    						"\n 3 - Sair"
							"\n Responda: ";
    	cout << menu;
    	cin >> opcao;
    	
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	
        if (opcao == 1){
        		cout << "Digite o nome da conta: ";
				getline(cin, nome_da_conta);
				
				for(int i=0; i < lista_de_usuarios.size(); i++){
					if(lista_de_usuarios[i].pegaNome() == nome_da_conta){
						cout << "Digite a senha do usuario: ";
						getline(cin, senha_da_conta);
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						if(lista_de_usuarios[i].pegaSenha() == senha_da_conta){
							menuUsuario(lista_de_usuarios[i].pegaId(),lista_de_videos,lista_de_planos);
						}
						else{
							cout<<"Informação de login incorreta"<<endl;
						}
					}
				}
		}
		else if (opcao == 2){
			cadastrarUsuario(lista_de_usuarios);
		}
		else if (opcao == 3){
			logoff = true;
		}
  }
    return 0;
}

HistoricoModel::HistoricoModel(int id_video, int id_usuario):
	id_video_(id_video), id_usuario_(id_usuario){}
UsuarioModel::UsuarioModel(int id, string nome, string senha, string tipo):
	id_(id), nome_(nome), senha_(senha), tipo_(tipo){}
VideoModel::VideoModel(int id, string nome, string duracao, string qualidade, string categoria, string tipo, int id_usuario):
	id_(id), nome_(nome), duracao_(duracao), qualidade_(qualidade), categoria_(categoria), tipo_(tipo), id_usuario_(id_usuario){}
PlanoModel::PlanoModel(int id, string nome, float preco, string data_expiracao, int id_usuario):
	id_(id), nome_(nome), preco_(preco), data_expiracao_(data_expiracao), id_usuario_(id_usuario){}
