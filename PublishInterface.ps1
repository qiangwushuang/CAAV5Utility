# �Զ������ӿ��ļ���ָ��Ŀ¼��

$PublishFrameworks = New-Object -TypeName System.Collections.ArrayList

$PublishFrameworks.Add("CommonFw")
$PublishFrameworks.Add("DatabaseFw")
$PublishFrameworks.Add("Base64Fw")
$PublishFrameworks.Add("DialogExt")
$PublishFrameworks.Add("ExcelOperatorFw")
$PublishFrameworks.Add("HTTPFw")
$PublishFrameworks.Add("JsonFw")
$PublishFrameworks.Add("MD5Fw")
$PublishFrameworks.Add("LicFw")


# ����ӿڷ���Ŀ¼
$PublishPath = "C:\DS\CAAV5Utility"

if (Test-Path "$PublishPath\win_b64") {   
    Remove-Item "$PublishPath\win_b64" -Force -Recurse
}

foreach($FrameworkName in $PublishFrameworks)
{
    $PublishFramework = ".\$FrameworkName"
    # ������Դ�ļ�
    if(Test-Path "$PublishFramework\CNext\*")
    {
        Copy-Item -Path "$PublishFramework\CNext\*" -Destination ".\win_b64" -Recurse -Force
    }
    # ɾ������Ҫ���ļ�
    Remove-Item ".\win_b64\code\dictionary\*DirForBinOMDictionary" -Force -Recurse
    Remove-Item ".\win_b64\code\dictionary\*SysCtrlWNTN.ctrl" -Force -Recurse
    Remove-Item ".\win_b64\code\bin\*.exe" -Force
    # ɾ�����еĽӿ�Ŀ¼
    if (Test-Path "$PublishPath$PublishFramework") {   
        Remove-Item "$PublishPath$PublishFramework" -Force -Recurse
    }

    # ��ȡ�ӿ��µ�moduleĿ¼����
    $ChilePath = Get-ChildItem -Path $PublishFramework
    foreach($path In $ChilePath)
    {
        $pathfullname = $path.FullName
        $pathname = $path.Name
        if($path.Name -like "*.m")
        {            
            mkdir "$PublishPath\$PublishFramework\$pathname" -Force
            Copy-Item -Path "$pathfullname\Imakefile.mk" -Destination "$PublishPath\$PublishFramework\$pathname\Imakefile.mk" -Force
        }
        elseif($path.Name -like "IdentityCard" -or $path.Name -like "Private*" -or $path.Name -like "Protected*" -or $path.Name -like "Public*" -or $path.Name -like "various")
        {
            Copy-Item -Path $pathfullname -Destination "$PublishPath\$PublishFramework\$pathname" -Force -Recurse
        }
    }
}
# win_b64Ŀ¼
Copy-Item ".\win_b64" -Destination "$PublishPath\win_b64" -Force -Recurse
