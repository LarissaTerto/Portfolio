
/**
 * 
 * @author Larissa Terto Alvim 13671765
 *
 */

public class Trabalho {

	enum Tipo {
		Peao, Bispo, Cavalo, Torre, Rei, Rainha;
	}

	enum Cor {
		Branca, Preta;
	}

	static class Peca {
		Tipo tipo;
		Cor cor;
		
		Peca() {
		}

		Peca(Tipo tipo_, Cor cor_) {
			tipo = tipo_;
			cor = cor_;
		}
	}

	/**
	 * @return Devolve o tabuleiro inicial, com as pe√ßas brancas embaixo e as pretas
	 *         em cima, considerando que a linha zero √© a linha superior da matriz
	 *         que representa o tabuleiro. As casas vazias devem conter a refer√™ncia
	 *         para null. Cada casa ocupada deve conter uma refer√™ncia para um
	 *         objeto do tipo "Peca", representando o tipo e a cor da pe√ßa que ocupa
	 *         a casa em quest√£o.
	 */
	
	static Peca[][] tabuleiroInicial() {
		Peca[][] tab = new Peca[8][8];
		Tipo[] tipos = {Tipo.Torre, Tipo.Cavalo, Tipo.Bispo, Tipo.Rainha, Tipo.Rei, Tipo.Bispo, Tipo.Cavalo, Tipo.Torre};
		Cor[] cores = {Cor.Preta, Cor.Branca};
		
		//pe„o
		for(int p = 0; p<8; p++) {
			tab[1][p] = new Peca(Tipo.Peao, cores[0]);
			tab[6][p] = new Peca(Tipo.Peao, cores[1]);
		}
		
		//torre, cavalo, bispo, rainha, rei
		for(int i = 0; i<8; i++) {
			tab[0][i] = new Peca(tipos[i], cores[0]);
			tab[7][i] = new Peca(tipos[i], cores[1]);
		}
		return tab;
	}
	
	/**
	 * @param l Linha onde est· uma casa do tabuleiro
	 * @param c Coluna onde est· uma casa do tabuleiro
	 * @return Retorna um valor booleano correspondente ‡ condiÁ„o dada para a casa estar dentro do tabuleiro        
	 */

	static boolean dentroTab(int l, int c) {
		return l>=0 && l<=7 && c>=0 && c<=7;
	}

	/**
	 *@param tab Representa o tabuleiro. Se tab[i][j] = null, ent„o a casa (i,j)
	 *           est· vazia. Caso contr·rio, tab[i][j] contÈm a peÁa que est· na
	 *           casa (i,j). Assuma que tab[l][c] contÈm uma peÁa.
	 *@param l Linha onde est· uma casa do tabuleiro
	 *@param c Coluna onde est· uma casa do tabuleiro
	 *@return Retorna um valor booleano correspondente ‡ condiÁ„o dada para a casa estar vazia
	 */
	
	static boolean vazia(Peca[][] tab, int l, int c) {
		return dentroTab(l, c) && tab[l][c] == null;
	}

	/**
	 *@param tab Representa o tabuleiro. Se tab[i][j] = null, ent„o a casa (i,j)
	 *           est· vazia. Caso contr·rio, tab[i][j] contÈm a peÁa que est· na
	 *           casa (i,j). Assuma que tab[l][c] contÈm uma peÁa.
	 *@param l Linha onde est· uma casa do tabuleiro
	 *@param c Coluna onde est· uma casa do tabuleiro
	 *@param cor Cor da peÁa jogada
	 *@return Retorna um valor booleano correspondente ‡ condiÁ„o dada para a casa 
	 *		  n„o estar vazia e possuir uma peÁa oponente, ou seja, de cor oposta
	 */
	
	static boolean temOponente(Peca[][] tab, int l, int c, Cor cor) {
		return dentroTab(l,c) && !vazia(tab,l, c) && tab[l][c].cor != cor;
	}
	
	/**
	 *@param tab Representa o tabuleiro. Se tab[i][j] = null, ent„o a casa (i,j)
	 *           est· vazia. Caso contr·rio, tab[i][j] contÈm a peÁa que est· na
	 *           casa (i,j). Assuma que tab[l][c] contÈm uma peÁa.
	 *@param l Linha onde est· uma casa do tabuleiro
	 *@param c Coluna onde est· uma casa do tabuleiro
	 *@param cor Cor da peÁa jogada
	 *@return Retorna um valor booleano correspondente ‡ condiÁ„o dada para a casa 
	 *		  estar vazia ou possuir uma peÁa oponente
	 */
	
	static boolean vaziaOuOponente(Peca[][] tab, int l, int c, Cor cor) {
		return vazia(tab, l, c) || temOponente(tab, l, c, cor);
	}
	
	/**
	 *@param tab Representa o tabuleiro. Se tab[i][j] = null, ent„o a casa (i,j)
	 *           est· vazia. Caso contr·rio, tab[i][j] contÈm a peÁa que est· na
	 *           casa (i,j). Assuma que tab[l][c] contÈm uma peÁa.
	 *@param l Linha onde est· a peÁa
	 *@param c Coluna onde est· a peÁa
	 *@param mov Matriz booleana 8 x 8, tal que, para toda casa (i,j) dentro do 
	 *           tabuleiro, mov[i][j] = true se e somente se a peÁa que est·° 
	 *           na casa (l,c) puder se movimentar para a casa (i,j)
	 *@param ll Vetor de inteiros correspondentes ao n˙mero de casas que peÁa pode avanÁar ou retornar na horizontal
	 *@param cc Vetor de inteiros correspondentes ao n˙mero de casas que peÁa pode avanÁar ou retornar na vertical
	 *@return Retorna as casas para onde a peÁa pode se mover
	 */
	
	
	static void movsDirecao(Peca[][] tab, int l, int c, boolean[][] mov, int[] ll, int[] cc){
		for(int d = 0; d<ll.length; d++){
			int x = l+ll[d];
			int y = c+cc[d];
			
			while(dentroTab(x,y)){
				if(vazia(tab, x, y)){
					mov[x][y] = true;
				} else if(temOponente(tab, x, y, tab[l][c].cor)){
					mov[x][y] = true;
					break;
				} else {
					break;
				}
				x+=ll[d];
				y+=cc[d];
			}
		}	
	}
	
	
	/**
	 * @param tab Representa o tabuleiro. Se tab[i][j] = null, ent√£o a casa (i,j)
	 *            est√° vazia. Caso contr√°rio, tab[i][j] cont√©m a pe√ßa que est√° na
	 *            casa (i,j). Assuma que tab[l][c] cont√©m uma peÁa.
	 * @param l   Linha em que esta a peÁa
	 * @param c   Coluna em que esta a peca
	 * @return Devolve uma matriz "mov" booleana 8 x 8, tal que, para toda casa
	 *         (i,j) dentro do tabuleiro, mov[i][j] = true se e somente se a peÁa
	 *         que est√° na casa (l,c) puder se movimentar para a casa (i,j)
	 * 
	 *         ATEN√á√ÉO: um movimento n√£o √© v√°lido se colocar o pr√≥prio rei em cheque
	 *         (por exemplo: se ao movimentar um pe√£o branco for aberta uma diagonal
	 *         entre o rei branco e um bispo preto, isso seria um "auto-cheque").
	 */
	
	static boolean[][] movsPeao(Peca[][] tab, int l, int c) {
		boolean[][] mov = new boolean[8][8];
		
		if(tab[l][c].cor == Cor.Preta){
			if(vazia(tab, l+1, c)) mov[l+1][c] = true;
			if(temOponente(tab, l+1, c+1, tab[l][c].cor)) mov[l+1][c+1] = true;
			if(temOponente(tab, l+1, c-1, tab[l][c].cor)) mov[l+1][c-1] = true;
		}
		
		if(tab[l][c].cor == Cor.Branca){
			if(vazia(tab, l-1, c)) mov[l-1][c] = true;
			if(temOponente(tab, l-1, c+1, tab[l][c].cor)) mov[l-1][c+1] = true;
			if(temOponente(tab, l-1, c-1, tab[l][c].cor)) mov[l-1][c-1] = true;
		}
		
		return mov;
	}

	static boolean[][] movsTorre(Peca[][] tab, int l, int c) {
		boolean[][] mov = new boolean[8][8];
		
		int[] ll = {0, -1, 0, 1};
		int[] cc = {-1, 0, 1, 0};
	
		movsDirecao(tab, l, c, mov, ll, cc);
		
		return mov;
	}

	static boolean[][] movsBispo(Peca[][] tab, int l, int c) {
		boolean[][] mov = new boolean[8][8];

		int[] ll = {-1, -1, 1, 1};
		int[] cc = {-1, 1, -1, 1};
	
		movsDirecao(tab, l, c, mov, ll, cc);	
		
		return mov;
	}

	static boolean[][] movsCavalo(Peca[][] tab, int l, int c) {
		boolean[][] mov = new boolean[8][8];

		int[] ll = {-2, -2, -1, 1, 2, 2, 1, -1};
		int[]cc = {-1, 1, 2, 2, 1, -1, -2, -2};
	
		for(int i = 0; i<ll.length; i++) {
			int x = l+ll[i];
			int y = c+cc[i];
			if(vaziaOuOponente(tab, x, y, tab[l][c].cor)) mov[x][y] = true;
		}
		return mov;
	}

	static boolean[][] movsRei(Peca[][] tab, int l, int c) {
		boolean[][] mov = new boolean[8][8];
		
		int[] ll = {0, 0, 1, 1, 1, -1, -1, -1};
		int[] cc = {-1, 1, -1, 0, 1, -1, 0, 1};
		
		for(int i = 0; i<8; i++) {
			int x = l+ll[i];
			int y = c+cc[i];
			if(vaziaOuOponente(tab, x, y, tab[l][c].cor)) mov[x][y] = true;
		}
		return mov;
	}

	static boolean[][] movsRainha(Peca[][] tab, int l, int c) {
		boolean[][] mov = new boolean[8][8];
		
		int[] ll = {-1, -1, 1, 1, 0, -1, 0, 1};
		int[] cc = {-1, 1, -1, 1, -1, 0, 1, 0};
	
		movsDirecao(tab, l, c, mov, ll, cc);
		
		return mov;
	}

	/**
	 * @param tab Representa o tabuleiro. Se tab[i][j] = null, ent„o a casa (i,j)
	 *            est· vazia. Caso contr·rio, tab[i][j] contÈm a peÁa que est· na
	 *            casa (i,j). Assuma que tab[l][c] contÈm uma peÁa.
	 * @param i Linha onde est· um oponente 
	 * @param j Coluna onde est· um oponente   
	 * @return Retorna uma matriz booleana 8x8 correspondente ‡ matriz booleana 
	 * 		   retornada pela funÁ„o que valida os movimentos de uma peÁa de certo tipo
	 */
	
	static boolean[][] verificarTipoDoOponente(Peca[][] tab, int i, int j) {
		boolean[][] movs = new boolean[8][8];
		Tipo[] tipos = {Tipo.Torre, Tipo.Cavalo, Tipo.Bispo, Tipo.Rainha, Tipo.Rei, Tipo.Peao};

		if(tab[i][j].tipo == tipos[0]) {
			movs = movsTorre(tab, i , j);
		} else if (tab[i][j].tipo == tipos[1]) {
			movs = movsCavalo(tab, i , j);
		} else if (tab[i][j].tipo == tipos[2]) {
			movs = movsBispo(tab, i , j);
		} else if (tab[i][j].tipo == tipos[3]) {
			movs = movsRainha(tab, i , j);
		} else if (tab[i][j].tipo == tipos[4]) {
			movs = movsRei(tab, i , j);
		} else if (tab[i][j].tipo == tipos[5]) {
			movs = movsPeao(tab, i , j);
		}
		
		return movs;
	}
	
	/**
	 * Recebe a cordenada (l,c) de um rei, que pode ser branco ou preto, e devolve
	 * verdadeiro se e somente se o rei est√° em cheque (ou seja, se o rei est√° sendo
	 * atacado por alguma pe√ßa do advers√°rio)
	 * 
	 * @param tab
	 * @param l   linha do rei
	 * @param c   coluna do rei
	 * @return
	 */
	
	static boolean estaEmCheque(Peca[][] tab, int l, int c) {
		for(int i  = 0; i<8; i++) {
			for(int j = 0; j<8; j++) {
				if(temOponente(tab, i, j, tab[l][c].cor)) {
					boolean[][] movs = verificarTipoDoOponente(tab, i, j);
					if(movs[l][c]){
						return true;
					} 
				}
			}
		}
		return false;
	}
}
