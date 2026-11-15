#include <iostream>
#include <string>
#include <exception>

using namespace std;

enum Categorie { STELE_3 = 3, STELE_4 = 4, STELE_5 = 5 };

class Hotel {
private:
	const int id;
	string denumire;
	Categorie categorie;
	int nrCamere;
	float* preturiCamere; 
public:
	static int nrHoteluri;

	Hotel() : id(++nrHoteluri) {
		this->denumire = "Hotel Anonim";
		this->categorie = STELE_3;
		this->nrCamere = 0;
		this->preturiCamere = nullptr;
	}

	Hotel(int id, string denumire, Categorie categorie, int nrCamere, float* preturiCamere) : id(id) {
		this->denumire = denumire;
		this->categorie = categorie;
		this->nrCamere = nrCamere;
		if (nrCamere > 0 && preturiCamere != nullptr) {
			this->preturiCamere = new float[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++) {
				this->preturiCamere[i] = preturiCamere[i];
			}
		}
		else {
			this->preturiCamere = nullptr;
			this->nrCamere = 0;
		}
		nrHoteluri++;
	}

	Hotel(const Hotel& h) : id(++nrHoteluri) {
		this->denumire = h.denumire;
		this->categorie = h.categorie;
		this->nrCamere = h.nrCamere;

		if (h.preturiCamere != nullptr) {
			this->preturiCamere = new float[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++) {
				this->preturiCamere[i] = h.preturiCamere[i];
			}
		}
		else {
			this->preturiCamere = nullptr;
		}
	}

	Hotel& operator=(const Hotel& h) {
		if (this == &h) {
			return *this;
		}

		this->denumire = h.denumire;
		this->categorie = h.categorie;
		this->nrCamere = h.nrCamere;

		if (this->preturiCamere != nullptr) {
			delete[] this->preturiCamere;
			this->preturiCamere = nullptr;
		}

		if (h.preturiCamere != nullptr) {
			this->preturiCamere = new float[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++) {
				this->preturiCamere[i] = h.preturiCamere[i];
			}
		}
		else {
			this->preturiCamere = nullptr;
		}

		return *this;
	}

	~Hotel() {
		if (this->preturiCamere != nullptr) {
			delete[] this->preturiCamere;
		}
	}

	void afisareHotel() const {
		cout << endl << "------------------------";
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Categorie: " << this->categorie << " stele";
		cout << endl << "Nr camere: " << this->nrCamere;

		if (this->nrCamere > 0 && this->preturiCamere != nullptr) {
			cout << endl << "Preturi camere: ";
			for (int i = 0; i < this->nrCamere; i++) {
				cout << this->preturiCamere[i] << " lei";
				if (i < this->nrCamere - 1) cout << ", ";
			}
		}
		cout << endl;
	}

	int getNrCamere() const {
		return this->nrCamere;
	}

	void setNrCamere(int nrCamereNou) {
		if (nrCamereNou >= 0) {
			this->nrCamere = nrCamereNou;
		}
		else {
			throw "Numarul de camere nu poate fi negativ!";
		}
	}

	bool operator<(const Hotel& h) const {
		return this->nrCamere < h.nrCamere;
	}

	friend ostream& operator<<(ostream& out, const Hotel& h) {
		out << "\n[Hotel ID: " << h.id << "] " << h.denumire 
			<< " | Categorie: " << h.categorie << " stele" 
			<< " | Camere: " << h.nrCamere;
		return out;
	}
};

int Hotel::nrHoteluri = 0;

class LantHoteluri {
private:
	const int idLant;
	string numeLant;
	int nrHoteluri;
	Hotel* listaHoteluri;
	static int totalLanturi;

public:
	LantHoteluri() : idLant(++totalLanturi) {
		this->numeLant = "Lant Anonim";
		this->nrHoteluri = 0;
		this->listaHoteluri = nullptr;
	}

	LantHoteluri(string numeLant, int nrHoteluri, Hotel* lista) : idLant(++totalLanturi) {
		this->numeLant = numeLant;
		this->nrHoteluri = nrHoteluri;
		if (nrHoteluri > 0 && lista != nullptr) {
			this->listaHoteluri = new Hotel[nrHoteluri];
			for (int i = 0; i < nrHoteluri; i++) {
				this->listaHoteluri[i] = lista[i];
			}
		} else {
			this->listaHoteluri = nullptr;
			this->nrHoteluri = 0;
		}
	}

	LantHoteluri(const LantHoteluri& l) : idLant(++totalLanturi) {
		this->numeLant = l.numeLant;
		this->nrHoteluri = l.nrHoteluri;
		if (l.listaHoteluri != nullptr && l.nrHoteluri > 0) {
			this->listaHoteluri = new Hotel[l.nrHoteluri];
			for (int i = 0; i < l.nrHoteluri; i++) {
				this->listaHoteluri[i] = l.listaHoteluri[i];
			}
		} else {
			this->listaHoteluri = nullptr;
		}
	}

	LantHoteluri& operator=(const LantHoteluri& l) {
		if (this == &l) {
			return *this;
		}
		this->numeLant = l.numeLant;
		this->nrHoteluri = l.nrHoteluri;

		if (this->listaHoteluri != nullptr) {
			delete[] this->listaHoteluri;
			this->listaHoteluri = nullptr;
		}

		if (l.listaHoteluri != nullptr && l.nrHoteluri > 0) {
			this->listaHoteluri = new Hotel[l.nrHoteluri];
			for (int i = 0; i < l.nrHoteluri; i++) {
				this->listaHoteluri[i] = l.listaHoteluri[i];
			}
		}

		return *this;
	}

	~LantHoteluri() {
		if (this->listaHoteluri != nullptr) {
			delete[] this->listaHoteluri;
			this->listaHoteluri = nullptr;
		}
	}

	Hotel& operator[](int index) {
		if (index >= 0 && index < this->nrHoteluri && this->listaHoteluri != nullptr) {
			return this->listaHoteluri[index];
		} else {
			throw out_of_range("Index invalid in lantul de hoteluri!");
		}
	}

	friend ostream& operator<<(ostream& out, const LantHoteluri& lant) {
		out << "\n===============================";
		out << "\nLant Hoteluri ID: " << lant.idLant;
		out << "\nNume Lant: " << lant.numeLant;
		out << "\nNumar hoteluri: " << lant.nrHoteluri;
		if (lant.listaHoteluri != nullptr && lant.nrHoteluri > 0) {
			out << "\nLista hoteluri:";
			for (int i = 0; i < lant.nrHoteluri; i++) {
				out << lant.listaHoteluri[i];
			}
		}
		out << "\n===============================" << endl;
		return out;
	}
};

int LantHoteluri::totalLanturi = 0;

int main() {
	Hotel hDefault;

	float* preturi = new float[4] {250.5f, 300.0f, 450.0f, 600.0f};
	Hotel* pHotelLux = new Hotel(10, "Grand Hotel", STELE_5, 4, preturi);

	Hotel* vectorHoteluri = new Hotel[2];
	vectorHoteluri[0] = hDefault;
	vectorHoteluri[1] = *pHotelLux;

	LantHoteluri lant1("Continental Group", 2, vectorHoteluri);
	cout << lant1;

	cout << endl << "Total hoteluri create individual: " << Hotel::nrHoteluri;

	if (hDefault < *pHotelLux) {
		cout << endl << "Hotelul default are mai putine camere decat cel de lux.";
	}

	delete[] vectorHoteluri;
	delete pHotelLux;

	return 0;
}