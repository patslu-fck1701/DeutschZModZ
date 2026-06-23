# Online Test Safe Boot

Expected startup log lines when the server actually loads `@DeutschZ_OperationDeutschZ`:

```text
[DeutschZ_OperationDeutschZ] Init start
[DeutschZ_OperationDeutschZ] Profile folders ensured
[DeutschZ_OperationDeutschZ] Config created
[DeutschZ_OperationDeutschZ] Config loaded
[DeutschZ_OperationDeutschZ] State created
[DeutschZ_OperationDeutschZ] State loaded
[DeutschZ_OperationDeutschZ] Init done
```

The local pipeline does not edit the server batch. If the batch does not include `@DeutschZ_OperationDeutschZ`, the pipeline can build, deploy and package the mod, but the boot log cannot appear until that batch or an online testserver modline loads it.
