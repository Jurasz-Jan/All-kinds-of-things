// C++ implementation of the above approach
#include <bits/stdc++.h>
#include <limits.h>
#include <iostream>
#include <climits>

using namespace std;

//Ilość punktów, obsłuży dość dużą liczbę. Niestety,musiałbym dostosować algorytm wypisywania stringów, by obsługiwać lczby większe od 9.
// trzeba by używać zwyczajnie liczb oddzielonych spacją zamiast stringu GNOME. 
//GNOME zrobiłem tak, by wyszukiwało znaki w stringu, by sprawdzić odwiedzone miesca.
#define V 9 //MAX 9.
int CostGraphMatrix[V][V];

#define GENES ABCDE

// startowy Node
#define START 0

// Rozmiar populacji dla algorytmu
#define POP_SIZE 10

//  GNOME
// string definiuje przebytą ścieżkę przez sprzedawce
//  fitness value ścieżki przechowuję w integerze


struct individual {
	string gnome;
	int fitness;
};

struct Point {
int x, y;
};

int dist(Point p1, Point p2) {
// dystans euklidesowy
return (int)sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
};


int rand_num(int start, int end)
{
	int r = end - start;
	int rnum = start + rand() % r;
	return rnum;
}

// Funkcja do sprawdzania, czy znak jest już w stringu.

bool repeat(string s, char ch)
{
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ch)
			return true;
	}
	return false;
}

//Funkcja do zwracania mutowanego GNOME
//Mutowany GNOME jest ciągiem znaków
//z losową zamianą dwóch genów, aby stworzyć różnorodność w gatunkach.
string mutatedGene(string gnome)
{
	while (true) {
		int r = rand_num(1, V);
		int r1 = rand_num(1, V);
		if (r1 != r) {
			char temp = gnome[r];
			gnome[r] = gnome[r1];
			gnome[r1] = temp;
			break;
		}
	}
	return gnome;
}

// Tworzę string GNOME
// który potrzebuję do stworzenia populacji
string create_gnome()
{
	string gnome = "0";
	while (true) {
		if (gnome.size() == V) {
			gnome += gnome[0];
			break;
		}
		int temp = rand_num(1, V);
		if (!repeat(gnome, (char)(temp + 48)))
			gnome += (char)(temp + 48);
	}
	return gnome;
}

// Funkcja do zwracania fitness value przez gnoma.
// Fitness value jest proporcjonalna do długości ścieżki,

int cal_fitness(string gnome,int map[V][V])
{
	
	int f = 0;
	for (int i = 0; i < gnome.size() - 1; i++) {
		if (map[gnome[i] - 48][gnome[i + 1] - 48] == INT_MAX)
			return INT_MAX;
		f += map[gnome[i] - 48][gnome[i + 1] - 48];
	}
	return f;
}

// Update temperatury

int cooldown(int temp)
{
	return (90 * temp) / 100;
}

// Porównuję atrakcyjność gnomów
bool lessthan(struct individual t1,
			struct individual t2)
{
	return t1.fitness < t2.fitness;
}


void TSPUtil(int map[V][V])
{
	// Numer generacji/pokolenia
	int gen = 1;
	// Ilość generacji UWAŻAĆ Z LICZBAMI, ALE I TAK NAJWAŻNIEJSZE TO UWAŻAĆ NA V.
	int gen_thres = 15;

	vector<struct individual> population;
	struct individual temp;

	// Populuję gnomy
	for (int i = 0; i < POP_SIZE; i++) {
		temp.gnome = create_gnome();
		temp.fitness = cal_fitness(temp.gnome, map);
		population.push_back(temp);
	}

	cout << "\nInitial population: " << endl
		<< "CHROMOSOME	 FITNESS VALUE\n";
	for (int i = 0; i < POP_SIZE; i++)
		cout << population[i].gnome << " "
			<< population[i].fitness << endl;
	cout << "\n";

	bool found = false;
	int temperature = 10000;

	// Iteracja do wykonywania
	// Krzyżowania populacji i mutacja genów.
	while (temperature > 1000 && gen <= gen_thres) {
		sort(population.begin(), population.end(), lessthan);
		cout << "\nCurrent temp: " << temperature << "\n";
		vector<struct individual> new_population;

		for (int i = 0; i < POP_SIZE; i++) {
			struct individual p1 = population[i];

			while (true) {
				string new_g = mutatedGene(p1.gnome);
				struct individual new_gnome;
				new_gnome.gnome = new_g;
				new_gnome.fitness = cal_fitness(new_gnome.gnome,map);

				if (new_gnome.fitness <= population[i].fitness) {
					new_population.push_back(new_gnome);
					break;
				}
				else {

					//Akceptacja odrzuconych dzieci z
					//możliwym prawdopodobieństwem powyżej progu.
					float prob = pow(2.7,				//można zmieniać
									-1 * ((float)(new_gnome.fitness
												- population[i].fitness)
										/ temperature));
					if (prob > 0.5) {
						new_population.push_back(new_gnome);
						break;
					}
				}
			}
		}

		temperature = cooldown(temperature);
		population = new_population;
		cout << "Generation " << gen << " \n";
		cout << "CHROMOSOME	 FITNESS VALUE\n";

		for (int i = 0; i < POP_SIZE; i++)
			cout << population[i].gnome << " "
				<< population[i].fitness << endl;
		gen++;
	}
}


void constructCostGraphMatrix(int num_points) {
    int x, y;
    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < num_points; j++) {
            if (i == j) {
                CostGraphMatrix[i][j] = 0;
                continue;
            }
            cin >> x >> y;
            CostGraphMatrix[x][y] = i + j;
        }
    }
}




	
	

void constructCostMatrix(int map[V][V], Point points[V]) {
	
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i == j) {
				map[i][j] = 0;
						}
			else {
				map[i][j] = dist(points[i], points[j]);
				}
		}
	}
}






int main(){
	
 Point points[V];
  cout <<"To algorytm genetyczny rozwiązywania TSP.\n Najlepiej sobie radzi dla dużych liczb \n. Obsługuje V punktów, polecam uważać ze zwiększaniem V\n."  << "Wpisz X i Y dla każdego punktu:" << endl;
  for (int i = 0; i < V; i++) {
    cout << "Punkt " << i + 1 << ": ";
    cin >> points[i].x >> points[i].y;
  }
int map[V][V];
constructCostMatrix(map, points);

for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
        cout << map[i][j] << " ";
    }
    cout << endl;
}
	
	TSPUtil(map);
	return 0;
}
