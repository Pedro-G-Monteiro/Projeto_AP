
# Projeto de Algoritmo e Programação - Grupo 11

## Introdução

Este projeto foi desenvolvido pelos alunos Alexandre Moreira, Artur Santos, Pedro Monteiro e Rodrigo Alves para a Unidade Curricular de Algoritmo e Programação, no primeiro ano da licenciatura. O objetivo do projeto é gerir contratos de clientes de uma empresa, incluindo a criação, eliminação, listagem e cálculo de estatísticas relacionadas aos consumos dos clientes.

## Estrutura do Projeto

O projeto é composto pelos seguintes módulos:

- **Main**: O ponto de entrada do programa que exibe o menu principal e redireciona o usuário para as diferentes áreas do sistema.
- **Gestão de Contratos**: Funções para criar, eliminar e listar contratos.
- **Gestão de Leituras**: Funções para adicionar leituras de consumo aos contratos.
- **Estatísticas**: Funções para calcular estatísticas como média de consumo por freguesia e número de contratos sem consumo.
- **Persistência de Dados**: Funções para guardar e ler dados de contratos em ficheiros de texto e binários.

## Funcionalidades

### Menu Principal

O menu principal oferece as seguintes opções:

1. Área de Clientes
2. Área da Empresa
3. Estatísticas
4. Sair e fazer Reset
5. Sair e Guardar

### Área de Clientes

Nesta área, os usuários podem:

- Criar um novo contrato
- Eliminar um contrato existente

### Área da Empresa

Nesta área, os usuários podem:

- Listar todos os contratos
- Listar a média de consumos por freguesia
- Adicionar uma leitura de consumo a um contrato
- Procurar um contrato pelo nome do cliente

### Estatísticas

Nesta seção, são apresentadas as seguintes estatísticas:

- Número total de contratos criados
- Número de contratos sem consumo

### Persistência de Dados

Os dados dos contratos são guardados automaticamente em ficheiros de texto e binários quando o programa encerra. Os ficheiros incluem:

- `Contratos.txt`
- `Contratos.dat`
- `Contratos Eliminados.txt`
- `Contratos Eliminados.dat`
- `Freguesias.txt`
- `Leituras.txt`

## Compilação e Execução

Para compilar e executar o programa, siga os seguintes passos:

1. Compile o código fonte com o comando:
   ```bash
   gcc -o projeto Grupo11_AlexandreMoreira_ArturSantos_PedroMonteiro_RodrigoAlves.c
   ```

2. Execute o programa:
   ```bash
   ./projeto
   ```

## Contribuidores

- Alexandre Moreira
- Artur Santos
- Pedro Monteiro
- Rodrigo Alves
