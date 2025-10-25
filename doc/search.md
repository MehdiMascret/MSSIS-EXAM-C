# Hashmap
Je savais que les hashmap n'etait pas que des pointeur qui pointe directement sur la valeur,
pour gérer les collission ils font des buckets où chaque pointeur est du type arbre noir rouge,
j'ai cherché plus de détail dans la doc java, je suis tombé pour les hashmap sur
**"le facteur de charge"**, j'ai cherché ce que c'etais, je suis tombé sur une page qui explique
**"Par exemple, si votre table de hachage peut contenir 100 éléments et contient actuellement 50 éléments,
le facteur de charge est de 0,5 (50%)."**
Donc on a un calcule qui permet d'obtenir ce facteur de charge et que plus ce facteur est faible mieux c'est !

En cherchant plus loin je suis suis tombé sur un calcul qui permet de passer outre le modulo pour etre plus rapide. 

Cet optimisation ne fonctionne que si `n est une puissance de 2` :
```c++
// n est la capcité
// Lent
int i = hash % n;
// Plus rapide quand on fixe (n-1) 
int i = (n-1) & hash
```

Dans le stackoverflow qui parle de cette optimisation on nous parle de **Computes key.hashCode() and spreads (XORs) higher bits of hash to lower**

De ce que j'ai compris, comme on fait un `and`, on utilise uniquement les bits en dessous de `capacity (n)`, donc on perd beaucoup d'espace d'utilisation sur les bits supérieur à `capacity (n)`

Il faut donc une méthode pour que les bits fort soit utiliser qui soit prévisible et pas aléatoire, comme en java :
```c++
int hash(int key) {
    int h;
    return (key == null) ? 0 : (h = key) ^ (h >> 16);
}
```

## Réferences

Super Doc trouvé : https://medium.com/@reetesh043/understanding-hashmap-in-java-f2fddb1f3b44

Buckets: Image interressant mais doit remplacer ArrayList par Tree pour notre example
https://stackoverflow.com/questions/37959941/what-exactly-is-bucket-in-hashmap

Début :
- https://stackoverflow.com/questions/7666509/hash-function-for-string
- https://docs.oracle.com/javase/8/docs/api/java/util/HashMap.html : Load facteur à 0.75 ?

### DJB2 :
- http://www.cse.yorku.ca/~oz/hash.html


### Capacity et load factor :
- C'est quoi un load factor ? : https://ironpdf.com/fr/blog/net-help/csharp-hashmap/
- https://stackoverflow.com/questions/7115445/what-is-the-optimal-capacity-and-load-factor-for-a-fixed-size-hashmap
  - Avoir le meuilleur load facteur, beaucoup de graphique
  - un calcul a la fin :  capacity = expectedSize / 0.75F + 1.0F origine : Google Guava, d'après Google Guava le meuilleur est capacity = ceil(expectedSize / 0.75F) avec loadFactor = 0.75

### Puissance de 2 :
Java conseille d'avoir une capacité qui est un modulo 2 pour des performances et de faire index = hash & (capacity - 1);
- https://stackoverflow.com/questions/36554000/understanding-method-comment-for-hash-method-of-hashmap-class-in-java-8
- https://runzhuoli.me/2018/09/20/why-hashmap-size-power-of-2.html
