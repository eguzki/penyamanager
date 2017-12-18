# DDBB DATA INITIALIZATION SCRIPT


Write-Host "********************************************************************************************" 
Write-Host "Has editado los headers del csv para que coincidan con los campos de las variables?"
Write-Host "********************************************************************************************" 
Read-Host "Pulsa INTRO para continuar"


#####    NSOCIO,NOMBRE,APELLIDOS,type,NTARJETA,ALTA,DIRECCION,CP,POBLACION,PROVINCIA,TELEFONO,TELEFONO2,email,NCUENTA,NOTES,Cuadro combinado36,NOMANDAR,birth

$users = Import-CSV -LiteralPath c:\penyamanager\memberlist.csv -Encoding UTF8

$count = 1

"USE alegria ;" >> c:\penyamanager\import.sql

ForEach($user in $users)
{
    
    $idmember = (1+$count)
    $username = $count
    $name = $user.nombre
    $name = (Get-Culture).textinfo.totitlecase($name.tolower())
    write-host $name

    #Check if more than 2 strings on APELLIDOS, if yes, manual entry.
    $surnames = $user.apellidos
    Write-Host $surnames
    if (( $surnames | Measure-Object -Word | select Words).Words -gt 2)
    {

        Write-Host "******************************"
        Write-Host "Apellidos en conflicto: "
        Write-Host "******************************"
        Write-Host "******************************"
        Write-Host $surnames
        Write-Host "******************************"
        Write-Host "******************************"

        $surname1 = Read-Host "Introduce 1er apellido:"
        $surname1 = (Get-Culture).textinfo.totitlecase($surname1.tolower())
        $surname2 = Read-Host "Introduce 2do apellido:"
        $surname2 = (Get-Culture).textinfo.totitlecase($surname2.tolower())

    }else{
    
        $surname1 , $surname2 = $surnames.split(" ")
        $surname1 = (Get-Culture).textinfo.totitlecase($surname1.tolower())
        $surname2 = (Get-Culture).textinfo.totitlecase($surname2.tolower())
        

    }
    
    if (![string]::IsNullOrEmpty($user.alta)){
        
        $reg_datepart = $user.alta -split "/"
        [string]$reg_date = "$($reg_datepart[2])-$($reg_datepart[1])-$($reg_datepart[0])"
        [string]$reg_date = $reg_date + " 00:00:00"
    
    }else{
        
        $reg_date = (get-date -Format "yyyy-MM-dd HH:mm:ss")

    }

    $lastmodified = $reg_date

    $active = 0
    $isAdmin = 0
        
    if (![string]::IsNullOrEmpty($user.birth)){
        
        $birthpart = $user.birth -split "/"
        [string]$birth = "$($birthpart[2])-$($birthpart[1])-$($birthpart[0])"

    
    }
        
    $address = $user.direccion
    $address = (Get-Culture).textinfo.totitlecase($address.tolower())
    $zip_code = $user.cp
    $town = $user.poblacion
    $town = (Get-Culture).textinfo.totitlecase($town.tolower())
    $state = $user.provincia
    $state = (Get-Culture).textinfo.totitlecase($state.tolower())
    $tel = $user.telefono
    $tel2 = $user.telefono2
    $email = $user.email
    $bank_account = $user.ncuenta
    $postal_send = $user.nomandar

    if ($postal_send -eq 0)
    {
        
        $postal_send = 1

    }else{

        $postal_send = 0

    }

    $notes = $user.notes
    $pwd = "9af15b336e6a9619928537df30b2e6a2376569fcf9d7e773eccede65606529a0"
    if (![string]::IsNullOrEmpty($user.alta)){
        
        $lastloginpart = $user.alta -split "/"
        [string]$lastlogin = "$($lastloginpart[2])-$($lastloginpart[1])-$($lastloginpart[0])"
        [string]$lastlogin = $lastlogin + " 00:00:00"
           
    }else{

        $lastlogin = $reg_date

    }

    $id_card = ""
    $card = $user.ntarjeta
    $type = $user.type
    switch ($type){

        "Baja Temporal" {$type = 0} 
        "Activo" {$type = 0}
        "Jubilado" {$type = 1}
        "Veterano" {$type = 2}
        default {$type = 0}

    }

    #Call function to insert line on SQL file to import

    Write-Host $idmember 
    Write-Host $username 
    Write-Host $name
    Write-Host $surname1
    Write-Host $surname2
    Write-Host $image
    Write-Host $lastmodified
    Write-Host $reg_date
    Write-Host $active
    Write-Host $isAdmin
    Write-Host $birth 
    Write-Host $address
    Write-Host $zip_code
    Write-Host $town
    Write-Host $statefads
    Write-Host $tel
    Write-Host $tel2
    Write-Host $email
    Write-Host $bank_account
    Write-Host $postal_send
    Write-Host $notes
    Write-Host $pwd
    Write-Host $lastlogin
    Write-Host $id_card
    Write-Host $card
    Write-Host $type 





    $line = "INSERT INTO member (idmember , username , name , surname1 , surname2 , image , lastmodified , reg_date , active , isAdmin , birth , address , zip_code , town , state , tel , tel2 , email , bank_account , postal_send , notes , pwd , lastlogin , id_card , card , type ) VALUES ($idmember , $username , `"$name`" , `"$surname1`" , `"$surname2`" , `"$image`" , `"$lastmodified`" , `"$reg_date`" , $active , $isAdmin , `"$birth`" , `"$address`" , `"$zip_code`" , `"$town`" , `"$state`" , `"$tel`" , `"$tel2`" , `"$email`" , `"$bank_account`" , $postal_send  , `"$notes`" , `"$pwd`" , `"$lastlogin`" , `"$id_card`" , `"$card`" , $type );"

    $line >> c:\penyamanager\import.sql

    if (![string]::IsNullOrEmpty($user.alta)){
        
        $accountdatepart = $user.alta -split "/"
        [string]$accountdate = "$($accountdatepart[2])-$($accountdatepart[1])-$($accountdatepart[0])"
        [string]$accountdate = $accountdate + " 00:00:00"

    }else{

        $accountdate = $reg_date

    }

    $line2 = "INSERT INTO account ( idmember ,  amount ,  date ,  balance ,  description ,  type ) VALUES ($idmember, 0 , `"$accountdate`" , 0 , `"`" , 0);"

    $line2 >> c:\penyamanager\import.sql

    $count = $count + 1
}


