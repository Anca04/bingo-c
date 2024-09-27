Pentru bingo:

Am folosit o matrice tridimensionala de tip intreg(carduri) in care retin 
cardurile si o matrice tridimensionala de tip char in care colorez celule cu 
#(celule).

Functia SHIFT se executa ciclic pana cand Y devine 0, mutand fiecare element 
cu cate o pozitie. Salvez ultimul element de pe coloana, iar apoi il 
repozitionez la inceputul acesteia.

Functia SWAP realizeaza atat intershimbarea coloanelor, cat si cea a 
intervalelor pentru ambele cazuri, numere si #, folosind un auxiliar.

Functia DSC/ASC ordoneaza descrescator/crescator coloana transmisa prin 
parcurgerea acesteia si compararea elementelor. Functioneaza atat pentru 
numere, cat si pentru #, folosind matricea in care am colorat.

Am folosit initializare_matrice pentru a colora celula din mijloc, si pentru 
a retine intervalele in bingo_index.

Functia celule_colorat coloreaza cu # in matricea celule. In vectorul citcel 
am salvat numerele bilelor citite, apoi parcurg atat vectorul cat si matricea 
carduri pentru a testa daca este necesara colorarea cu #. De asemenea testez 
daca valorile din vectorul citcel corespund fiecarui interval atribuit 
coloanei respective.

Functia WINNER testeaza pentru fiecare caz, pe coloane, pe linii, pe diagonala 
principala, pe diagonala secundara, daca exista combinatia de 5 #. Salvez 
intr-un vector winner cardurile castigatoare, retinand astfel si ID-ul, iar 
intr-un vector puncteNou retin punctele pentru fiecare card.

Functia citire_bile citeste bilele de la tastatura, apoi extrag numerele din 
fiecare comanda citita si le salvez intr-un vector. Bilele speciale sunt 
salvate cu valoarea -1, pentru a nu afecta colorarea cu #. Apelez functiile 
introduse de la tastaura. La final testez daca un card este castigator sau nu. 

