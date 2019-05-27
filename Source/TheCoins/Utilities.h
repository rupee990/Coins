
#include "CoreMinimal.h"

namespace Util
{
    //Converts 3D Vector into 2D and returns the direction.
    FVector2D GetDirection2D(FVector A, FVector B)
    {
        FVector2D dir2D = FVector2D(B.X - A.X, B.Y - A.Y);
        dir2D.Normalize();

        return dir2D;
    }

    FVector GetDirection(FVector A, FVector B)
    {
        FVector dir = FVector(B.X - A.X, B.Y - A.Y, B.Z - A.Z);
        dir.Normalize();

        return dir;
    }
}
