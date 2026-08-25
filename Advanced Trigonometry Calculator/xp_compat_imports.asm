.386
.model flat

EXTERN _atcInitializeCriticalSectionEx@12:PROC
EXTERN _atcFlsAlloc@4:PROC
EXTERN _atcFlsFree@4:PROC
EXTERN _atcFlsGetValue@4:PROC
EXTERN _atcFlsSetValue@8:PROC
EXTERN _atcIsThreadAFiber@0:PROC

.data
PUBLIC __imp__InitializeCriticalSectionEx@12
PUBLIC __imp__FlsAlloc@4
PUBLIC __imp__FlsFree@4
PUBLIC __imp__FlsGetValue@4
PUBLIC __imp__FlsSetValue@8
PUBLIC __imp__IsThreadAFiber@0

__imp__InitializeCriticalSectionEx@12 DD OFFSET _atcInitializeCriticalSectionEx@12
__imp__FlsAlloc@4 DD OFFSET _atcFlsAlloc@4
__imp__FlsFree@4 DD OFFSET _atcFlsFree@4
__imp__FlsGetValue@4 DD OFFSET _atcFlsGetValue@4
__imp__FlsSetValue@8 DD OFFSET _atcFlsSetValue@8
__imp__IsThreadAFiber@0 DD OFFSET _atcIsThreadAFiber@0

END
