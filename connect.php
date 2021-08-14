<html>
<body>

<?php

$dbname = 'XXXXX'; //Nome do Banco de Dados
$dbuser = 'XXXXX'; //Nome do usuario que vai Logar
$dbpass = 'XXXXX'; //Senha do usuario
$dbhost = 'XXXXX'; //Endereço hospedado o Banco

$connect = @mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

if(!$connect){
	echo "Erro: " . mysqli_connect_error();
	exit();
}

echo "Sucesso na Conexão!<br><br>";

$temperatura_ninho = $_GET["temperatura_ninho"];
$umidade_ninho = $_GET["umidade_ninho"]; 

$temperatura_melgueira = $_GET["temperatura_melgueira"];
$umidade_melgueira = $_GET["umidade_melgueira"]; 


$id_caixa = $_GET["id_caixa"]; 


$query = "INSERT INTO boxMelgueira (temperatura_ninho, umidade_ninho, temperatura_melgueira, umidade_melgueira, id_caixa) VALUES ('$temperatura_ninho', '$umidade_ninho', '$temperatura_melgueira', '$umidade_melgueira', '$id_caixa')";
$result = mysqli_query($connect,$query);

echo "Sucesso ao Inserir Dados!<br>";

?>
</body>
</html>