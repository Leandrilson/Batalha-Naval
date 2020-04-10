#include <iostream>
#include <locale>
#include <ctime>
using namespace std;

char Num1[12] = { ' ','1','2','3','4','5','6','7','8','9','1',' ' };
char Num2[12] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','0',' ' };
char Let[12] = { ' ','A','B','C','D','E','F','G','H','I','J',' ' };

int CampoLargura = 10;
int CampoAltura = 10;

char** Campo;
int** Navios;

class Navio {
private:
	int ID;
	int tamanho;
	int acertos;
	int orientacao; //0=horizontl, 1=vertical
	int xInicial;
	int yInicial;
public:
	Navio() {}
	Navio(int tamanho, int id)
	{
		this->ID = id;
		this->tamanho = tamanho;
		this->acertos = 0;
		this->orientacao = rand() % 2;
	}
	void setAcertos(int i)
	{
		this->acertos = i;
	}
	void setXInicial(int x)
	{
		this->xInicial = x;
	}
	void setYInicial(int y)
	{
		this->yInicial = y;
	}
	int getID()
	{
		return this->ID;
	}
	int getAcertos()
	{
		return this->acertos;
	}
	int getTamanho()
	{
		return this->tamanho;
	}
	int getOrientacao()
	{
		return this->orientacao;
	}
	int getXInicial()
	{
		return this->xInicial;
	}
	int getYInicial()
	{
		return this->yInicial;
	}
};

//Funções relacionadas ao posicionamento de navios

bool Valida(int x, int y)
{
	if (Navios[x][y] == 0) return true;
	else return false;
}

void DesenharNavio(int tamanho, int id, int orientacao, int x, int y)
{
	if (orientacao == 0)
	{
		for (int i = 0; i < tamanho;i++)
		{
			Navios[x + i][y] = id;
		}
	}
	else
	{
		for (int i = 0; i < tamanho;i++)
		{
			Navios[x][y+i] = id;
		}
	}
}

void Posicionar(Navio* navio)
{
	int x, y, o;
	bool posicao_valida = false;
	o = navio->getOrientacao();

	if (o == 0)
	{
		while (!posicao_valida)
		{
			x = rand() % (CampoLargura - navio->getTamanho() + 1);
			y = rand() % CampoAltura;
			posicao_valida = true;
			for (int i = 0;i < navio->getTamanho();i++)
			{
				if (!Valida(x + i, y))
				{
					posicao_valida = false;
					break;
				}
			}
		}
	}
	else
	{
		while (!posicao_valida)
		{
			x = rand() % CampoLargura;
			y = rand() % (CampoAltura - navio->getTamanho() + 1);
			posicao_valida = true;
			for (int i = 0;i < navio->getTamanho();i++)
			{
				if (!Valida(x, y + i))
				{
					posicao_valida = false;
					break;
				}
			}
		}
	}

	navio->setXInicial(x);
	navio->setYInicial(y);

	DesenharNavio(navio->getTamanho(), navio->getID(), navio->getOrientacao(), navio->getXInicial(), navio->getYInicial());
}

void PrintNavios()
{
	for (int y = 0; y < CampoAltura + 3; y++)
	{
		for (int x = 0; x < CampoLargura + 3; x++)
		{
			if (x == 0 && y == 0)
				cout << "  ";
			else if (y == 0 && !x == 0)
			{
				cout << Let[x - 1];
			}
			else if (x == 0 && !y == 0)
			{
				cout << Num1[y - 1] << Num2[y - 1];
			}

			else if (y == 1 || y == CampoAltura + 2 || x == 1 || x == CampoLargura + 2)
				cout << "#";
			else cout << Navios[x - 2][y - 2];

			if (x == CampoLargura + 2) cout << endl;
			else cout << ' ';
		}
	}
}

//Funções relacionadas ao funcionamento do jogo

int Ataque()
{
	char cx;
	int x, y;
	cout << endl << "Insira a coordenada do seu ataque." << endl;

	cin >> cx >> y;
	x = (int)cx - 64;

	if (x < 1 || x > 10 || y < 1 || y > 10)
	{
		cout << "Input inválido." << endl;
		return Ataque();
	}

	if (Campo[x - 1][y - 1] != ' ')
	{
		cout << "Você já atingiu essa coordenada." << endl;
		return Ataque();
	}

	int resultado = Navios[x - 1][y - 1];

	if (resultado == 0)
	{
		Campo[x - 1][y - 1] = 'O';
	}
	else
	{
		Campo[x - 1][y - 1] = 'X';
	}

	return resultado;
}

//Função relacionadas a desenhar o campo

void PrintCampo()
{
	for (int y = 0; y < CampoAltura+3; y++) 
	{
		for (int x = 0; x < CampoLargura+3; x++)
		{
			if (x == 0 && y == 0)
				cout << "  ";
			else if (y==0 && !x==0)
			{
				cout << Let[x-1];
			}
			else if (x==0 && !y==0)
			{
				cout << Num1[y-1] << Num2[y-1];
			}

			else if (y == 1 || y == CampoAltura + 2 || x == 1 || x == CampoLargura + 2)
				cout << "#";
			else cout << Campo[x - 2][y - 2];

			if (x == CampoLargura + 2) cout << endl;
			else cout << ' ';
		}
	}
	cout << endl;
}

int main()
{
	std::locale::global(std::locale(""));
	//Intro
	cout << "===============================================================" << endl;
	cout << "BATALHA NAVAL SUPER INCRÍVEL DO LEANDRILSON" << endl;
	cout << "===============================================================" << endl;
	cout << "Insira 'I' para ler as instruções, e 'J' para começar o jogo." << endl;

	char option;
	cin >> option;
	if (option == 'I')
	{
		cout << "===============================================================" << endl;
		cout << "  O inimigo tem cinco navios, um porta aviões de tamanho 5, um" << endl;
		cout << "cruzador de tamanho 4, um destróier de tamanho 3, uma fragata" << endl;
		cout << "de tamanho 3 e um submarino de tamanho 2." << endl;
		cout << "  Para inserir corretamente a coordenada do ataque, insira uma" << endl;
		cout << "letra maiúscula seguida de um espaço eu um número." << endl;
		cout << "  No mapa, acertos em navios inimigos serão marcados com um" << endl;
		cout << "'X', e acertos em água com um 'O'." << endl;
		cout << "  Você tem 60 tiros para afundar os cinco navios inimigos." << endl;
		cout << "  Preste atenção nas informações exibidas na tela, elas te" << endl;
		cout << "dirão quando um navio inimigo foi naufragado." << endl;
		cout << "===============================================================" << endl;

		cout << "Insira 'J' para começar o jogo." << endl;
		cin >> option;
	}


	srand(time(0));
	//Inicializar Campo
	Campo = new char*[CampoLargura];
	for (int i = 0; i < CampoLargura; i++) Campo[i] = new char[CampoAltura];

	for (int i= 0;i < CampoLargura;i++)
		for (int j = 0;j < CampoAltura;j++)
			Campo[i][j] = ' ';

	Navios = new int* [CampoLargura];
	for (int i = 0; i < CampoLargura; i++) Navios[i] = new int[CampoAltura];

	for (int i = 0;i < CampoLargura;i++)
		for (int j = 0;j < CampoAltura;j++)
			Navios[i][j] = 0;


	//Inicializar Navios
	Navio PortaAvioes(5,5);
	Navio Cruzador(4,4);
	Navio Fragata(3,3);
	Navio Destroier(3,2);
	Navio Submarino(2,1);

	//Posicionar Navios
	Posicionar(&PortaAvioes);
	Posicionar(&Cruzador);
	Posicionar(&Fragata);
	Posicionar(&Destroier);
	Posicionar(&Submarino);

	//Game Loop
	bool GameOver = false;
	int event = 0; //1=água, 2=acerto, 3-7=navios naufragados, 8=vitória, 9=derrota
	int navios_restantes = 5;
	int resultado;
	int tiros = 60;

	while (!GameOver)
	{
		system("CLS");
		PrintCampo();

		//Informações

		if (event != 0)
		{
			cout << "===============================================================" << endl;
			switch (event)
			{
			case 1:
				cout << "Água!" << endl;
				break;
			case 2:
				cout << "Você acertou um navio inimigo!" << endl;
				break;
			case 3:
				cout << "Você naufragou o submarino inimigo!" << endl;
				break;
			case 4:
				cout << "Você naufragou o destróier inimigo!" << endl;
				break;
			case 5:
				cout << "Você naufragou a fragata inimiga!" << endl;
				break;
			case 6:
				cout << "Você naufragou o cruzador inimigo!" << endl;
				break;
			case 7:
				cout << "Você naufragou o porta aviões inimigo!" << endl;
				break;
			case 8:
				cout << "Parabéns, você destruiu todos os navios inimigos!" << endl;
				break;
			case 9:
				cout << "Seus tiros acabaram, infelizmente você perdeu. Que Pena!" << endl;
				break;
			}
			cout << "===============================================================" << endl;
			if (event == 9);
			else if (event == 8)
			{
				cout << "Você venceu com " << tiros << " tiros restantes!" << endl;
				cout << "===============================================================" << endl;
			}
			else
			{
				cout << "Você tem " << tiros << " tiros restantes." << endl;
				cout << "===============================================================" << endl;
			}
		}
		else
		{
			cout << "===============================================================" << endl;
			cout << "Você tem " << tiros << " tiros restantes." << endl;
			cout << "===============================================================" << endl;
		}

		//Lógica do jogo

		if (event == 8 || event == 9)
		{
			GameOver = true;
			break;
		}

		resultado = Ataque();
		tiros -= 1;

		switch (resultado)
		{
		case 0:
			event = 1;
			break;
		case 1:
			Submarino.setAcertos(Submarino.getAcertos() + 1);
			if (Submarino.getAcertos() == Submarino.getTamanho()) event = 3;
			else event = 2;
			break;
		case 2:
			Destroier.setAcertos(Destroier.getAcertos() + 1);
			if (Destroier.getAcertos() == Destroier.getTamanho()) event = 4;
			else event = 2;
			break;
		case 3:
			Fragata.setAcertos(Fragata.getAcertos() + 1);
			if (Fragata.getAcertos() == Fragata.getTamanho()) event = 5;
			else event = 2;
			break;
		case 4:
			Cruzador.setAcertos(Cruzador.getAcertos() + 1);
			if (Cruzador.getAcertos() == Cruzador.getTamanho()) event = 6;
			else event = 2;
			break;
		case 5:
			PortaAvioes.setAcertos(PortaAvioes.getAcertos() + 1);
			if (PortaAvioes.getAcertos() == PortaAvioes.getTamanho()) event = 7;
			else event = 2;
			break;
		}

		if (tiros == 0) event = 9;

		if (event == 3 || event == 4 || event == 5 || event == 6 || event == 7)
		{
			navios_restantes -= 1;
		}
		if (navios_restantes == 0) event = 8;

	}
	
	for (int i = 0; i < CampoLargura; i++) delete Campo[i];
	for (int i = 0; i < CampoLargura; i++) delete Navios[i];
	delete Campo;
	delete Navios;

	return 0;
}

//---Made by Leandro---//
