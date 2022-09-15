/*  https://www.opennet.ru/docs/RUS/MPI_intro/mpi_ex6.c.txr
 *  ex6.c  --  ������ 6       ��.�����  --  http://www.csa.ru/~il/mpi_tutor
 *
 *  �������� �������������-���������, �������� ���������� ������� ���������:
 *     MPI_Comm_dup, MPI_Comm_free
 *
 *  ���������� ������ � ��������� ������ �����
 *     MPI_Abort, MPI_Barrier
 */

#include <mpi.h>
#include <stdio.h>

#define  tag1  1
#define  tag2  2
#define  tag3  1   /* ������������ "������": ������������� ����� 'tag1' */

#define  ELEMS(x)  (sizeof( x )/sizeof( x[0] ))

int main( int argc, char **argv )
{
    MPI_Comm myComm;
    int rank, size;

    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

      /* ��������� ������ "�������� ���������� ���������� �����" */
    if( size != 2 && rank==0 ) {
        printf( "ERROR: 2 processes required instead of %d, abort.\n", size );
        MPI_Abort( MPI_COMM_WORLD, MPI_ERR_OTHER );
    }
      /* ������ �����, ����� � ������ ������, ���� ����� 0 ���������
       * � ��� � �������� MPI_Abort, ��������� ����� �� ������ ����������
       * � ���������� �������������� ����� ���������.
       */
    MPI_Barrier( MPI_COMM_WORLD );

      /**  ����� ����� ���������, ���������� �������������� �����... **/

      /* ������� ��� ���� ������������ - ����� MPI_COMM_WORLD */
    MPI_Comm_dup( MPI_COMM_WORLD, &myComm );

    if( rank == 0 )   /*  ����� 0 ��������  */
    {
        static char buf1[] = "Contents of first message";
        static char buf2[] = "Contents of second message";
        static char buf3[] = "Contents of third message";

          /* �������� ��������: ���� ��� ��������� ������ ���� � ��� ��
           * �������������, ��������� ������� ����� ������
           */  
        MPI_Send( buf1, ELEMS(buf1), MPI_CHAR, 1, tag1, myComm );
        MPI_Send( buf2, ELEMS(buf2), MPI_CHAR, 1, tag2, MPI_COMM_WORLD );
        MPI_Send( buf3, ELEMS(buf3), MPI_CHAR, 1, tag3, MPI_COMM_WORLD );
    }
    else     /*  ����� 1 ���������  */
    {
        char buf1[100], buf2[100], buf3[100];
        MPI_Status st;

          /* ����� �� ���������� ������ ��������� ��-�� ����, ��� tag1=tag3 */
        MPI_Recv( buf3, ELEMS(buf3), MPI_CHAR, 0, tag3, MPI_COMM_WORLD, &st );

          /* ����� �� ���������� ������ ��������� �������� */
        MPI_Recv( buf2, ELEMS(buf2), MPI_CHAR, 0, MPI_ANY_TAG,
            MPI_COMM_WORLD, &st );

          /* ������ ��������� ����� ������� ������� ���, ��� ���� */
        MPI_Recv( buf1, ELEMS(buf1), MPI_CHAR, 0, tag1, myComm, &st );

          /* �������� ���������� ������ */
        printf("Received in buf1 = \'%s\'\n", buf1 );
        printf("Received in buf2 = \'%s\'\n", buf2 );
        printf("Received in buf3 = \'%s\'\n", buf3 );

    } /* rank 1 */

      /* ���������� MPI, ��� ������ �������������� �� ����������.
       * ����� ����� myComm ����� ������� � MPI_COMM_NULL (�� ���� � 0),
       * � ��������������� ��� ������ ����� �������� �� ��������.
       */
    MPI_Comm_free( &myComm );

    MPI_Finalize();
}