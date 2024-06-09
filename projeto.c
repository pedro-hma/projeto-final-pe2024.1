#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_PLYLST 200
#define TAM_NOME 50
#define TAM_LOGIN 15
#define TAM_SENHA 15
#define TAM_PLAYLIST 100
#define TAM_TITULO 50
#define TAM_MUSICAS 100
#define ADMIN_PASSWORD "m@st3r2024"

struct Musica {
  int codigo;
  char titulo[TAM_TITULO];
  char artista[TAM_NOME];
};

struct Playlist {
  int codigo;
  int codUsuario;
  char titulo[TAM_TITULO];
  int qtdMusicas;
  int musicas[TAM_MUSICAS];
};

struct Usuario {
  int codigo;
  char nome[TAM_NOME];
  char login[TAM_LOGIN];
  char senha[TAM_SENHA];
  int qtdPlaylists;
  struct Playlist playlists[TAM_PLAYLIST];
  int qtdPlaylistsFav;
  int playlistsFav[TAM_PLAYLIST];
};

struct Usuario usuarios[TAM_MAX_PLYLST];
struct Musica musicas[TAM_MUSICAS];
int contUsuarios = 0, contMusicas = 0;

int gerarCodigo(int *contador) { return ++(*contador); }

void inicializarDados() {
  strcpy(usuarios[0].nome, "Administrador");
  strcpy(usuarios[0].login, "admin");
  strcpy(usuarios[0].senha, "admin");
  usuarios[0].codigo = gerarCodigo(&contUsuarios);
}

void exibirMenuInicial() {
  printf("Escolha uma opção:\n");
  printf("1. Administrador\n");
  printf("2. Usuário\n");
  printf("0. Sair\n");
}

int loginAdministrador() {
  char senha[TAM_SENHA];
  printf("Digite a senha de administrador: ");
  scanf("%s", senha);
  if (strcmp(senha, ADMIN_PASSWORD) == 0) {
    return 1;
  } else {
    printf("Senha incorreta!\n");
    return 0;
  }
}

void cadastrarMusica() {
  if (contMusicas >= TAM_MUSICAS) {
    printf("Capacidade máxima de músicas atingida!\n");
    return;
  }
  struct Musica novaMusica;
  novaMusica.codigo = gerarCodigo(&contMusicas);
  printf("Digite o título da música: ");
  scanf(" %[^\n]", novaMusica.titulo);
  printf("Digite o nome do artista: ");
  scanf(" %[^\n]", novaMusica.artista);
  musicas[contMusicas - 1] = novaMusica;
  printf("Música cadastrada com sucesso!\n");
}

void listarMusicas() {
  if (contMusicas == 0) {
    printf("Nenhuma música cadastrada!\n");
    return;
  }
  for (int i = 0; i < contMusicas; i++) {
    printf("Código: %d, Título: %s, Artista: %s\n", musicas[i].codigo,
           musicas[i].titulo, musicas[i].artista);
  }
}

void listarUsuarios() {
  if (contUsuarios == 0) {
    printf("Nenhum usuário cadastrado!\n");
    return;
  }
  for (int i = 0; i < contUsuarios; i++) {
    printf("Código: %d, Nome: %s, Login: %s\n", usuarios[i].codigo,
           usuarios[i].nome, usuarios[i].login);
  }
}

void consultarUsuario() {
  int codigo;
  printf("Digite o código do usuário: ");
  scanf("%d", &codigo);

  for (int i = 0; i < contUsuarios; i++) {
    if (usuarios[i].codigo == codigo) {
      printf("Código: %d, Nome: %s, Login: %s\n", usuarios[i].codigo,
             usuarios[i].nome, usuarios[i].login);
      return;
    }
  }
  printf("Usuário não encontrado!\n");
}

void alterarSenhaUsuario() {
  int codigo;
  char novaSenha[TAM_SENHA];
  printf("Digite o código do usuário: ");
  scanf("%d", &codigo);

  for (int i = 0; i < contUsuarios; i++) {
    if (usuarios[i].codigo == codigo) {
      printf("Digite a nova senha: ");
      scanf("%s", novaSenha);
      strcpy(usuarios[i].senha, novaSenha);
      printf("Senha alterada com sucesso!\n");
      return;
    }
  }
  printf("Usuário não encontrado!\n");
}

void consultarMusicas() {
  int codigo;
  printf("Digite o código da música: ");
  scanf("%d", &codigo);

  for (int i = 0; i < contMusicas; i++) {
    if (musicas[i].codigo == codigo) {
      printf("Código: %d, Título: %s, Artista: %s\n", musicas[i].codigo,
             musicas[i].titulo, musicas[i].artista);
      return;
    }
  }
  printf("Música não encontrada!\n");
}

void alterarDadosMusicas() {
  int codigo;
  printf("Digite o código da música: ");
  scanf("%d", &codigo);

  for (int i = 0; i < contMusicas; i++) {
    if (musicas[i].codigo == codigo) {
      printf("Digite o novo título da música: ");
      scanf(" %[^\n]", musicas[i].titulo);
      printf("Digite o novo nome do artista: ");
      scanf(" %[^\n]", musicas[i].artista);
      printf("Dados da música alterados com sucesso!\n");
      return;
    }
  }
  printf("Música não encontrada!\n");
}

void excluirMusicas() {
  int codigo;
  printf("Digite o código da música: ");
  scanf("%d", &codigo);

  for (int i = 0; i < contMusicas; i++) {
    if (musicas[i].codigo == codigo) {
      for (int j = i; j < contMusicas - 1; j++) {
        musicas[j] = musicas[j + 1];
      }
      contMusicas--;
      printf("Música excluída com sucesso!\n");
      return;
    }
  }
  printf("Música não encontrada!\n");
}

void listarPlaylists() {
  for (int i = 0; i < contUsuarios; i++) {
    for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
      printf("Código: %d, Título: %s, Código do Usuário: %d\n",
             usuarios[i].playlists[j].codigo, usuarios[i].playlists[j].titulo,
             usuarios[i].codigo);
    }
  }
}

void consultarPlaylists() {
  int codigo;
  printf("Digite o código da playlist: ");
  scanf("%d", &codigo);

  for (int i = 0; i < contUsuarios; i++) {
    for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
      if (usuarios[i].playlists[j].codigo == codigo) {
        printf("Código: %d, Título: %s, Código do Usuário: %d\n",
               usuarios[i].playlists[j].codigo, usuarios[i].playlists[j].titulo,
               usuarios[i].codigo);
        return;
      }
    }
  }
  printf("Playlist não encontrada!\n");
}

void menuUsuario() {
  printf("Função menuUsuario ainda não implementada.\n");
}

void menuAdministrador() {
  int opcao;
  do {
    printf("\nMenu do Administrador\n");
    printf("1. Listar usuários\n");
    printf("2. Consultar usuário\n");
    printf("3. Alterar senha de usuário\n");
    printf("4. Cadastrar novas músicas\n");
    printf("5. Listar todas as músicas\n");
    printf("6. Consultar músicas\n");
    printf("7. Alterar dados de músicas\n");
    printf("8. Excluir músicas\n");
    printf("9. Listar todas as playlists\n");
    printf("10. Consultar playlists\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      listarUsuarios();
      break;
    case 2:
      consultarUsuario();
      break;
    case 3:
      alterarSenhaUsuario();
      break;
    case 4:
      cadastrarMusica();
      break;
    case 5:
      listarMusicas();
      break;
    case 6:
      consultarMusicas();
      break;
    case 7:
      alterarDadosMusicas();
      break;
    case 8:
      excluirMusicas();
      break;
    case 9:
      listarPlaylists();
      break;
    case 10:
      consultarPlaylists();
      break;
    case 0:
      printf("Saindo do menu do administrador...\n");
      break;
    default:
      printf("Opção inválida!\n");
      break;
    }
  } while (opcao != 0);
}

// Função principal do programa
int main() {
  int opcao;
  inicializarDados();

  do {
    exibirMenuInicial();
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      if (loginAdministrador()) {
        menuAdministrador();
      }
      break;
    case 2:
      menuUsuario();
      break;
    case 0:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida!\n");
      break;
    }
  } while (opcao != 0);

  return 0;
}