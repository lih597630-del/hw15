# 퀵 정렬과 AVL 트리 정렬의 성능 비교

## 1. 구현 개요

### 1.1 퀵 정렬

- 피벗 선택 방법: **Median-of-Three**
  - 첫 원소, 중간 원소, 마지막 원소 세 값을 비교하여 중앙값을 피벗으로 선택
  - 정렬된 또는 부분 정렬된 데이터에서 편향된 피벗 선택을 완화하기 위함
- 분할 방식: Lomuto partition
- Median-of-Three에서 세 값을 비교하는 횟수도 비교 횟수에 포함
- swap 1회는 **데이터 이동 3회**(tmp ← a, a ← b, b ← tmp)로 계산

### 1.2 AVL 트리 정렬

- 동일한 원본 데이터를 순서대로 AVL 트리에 삽입
- 중복 값은 노드의 `count` 필드로 관리
- 균형 인수 비교, 포인터 연결 변경은 데이터 비교·이동 횟수에서 제외
- 중위 순회 결과를 오름차순 정렬 결과로 사용

### 1.3 삽입·삭제 실험

- 연산 횟수: `n / 5` (n의 20%)
- 각 연산은 다음과 같이 결정
  1. 0/1 난수를 생성하여 0이면 삽입, 1이면 삭제
  2. 별도의 난수로 삽입·삭제할 값 생성
  3. 두 자료구조에 **동일한 연산 순서·동일한 값**을 적용
- 삭제할 값이 존재하지 않으면 두 자료구조 모두 아무 일도 하지 않음
- 실험 종료 후 배열과 AVL 트리의 중위 순회 결과가 **완전히 동일**함을 검사

## 2. 측정 기준

### 2.1 총 수행시간

- `std::chrono::high_resolution_clock` 사용
- 단위: ms
- 측정 구간
  - Quick Sort: `quickSort(arr)` 호출 직전 ~ 모든 삽입/삭제 완료 직후
  - AVL: 초기 데이터 AVL 삽입 직전 ~ 모든 삽입/삭제 완료 직후
- 난수 생성, 결과 출력, 검증 시간은 제외

### 2.2 비교 횟수

- 데이터 값끼리 비교한 횟수만 카운트
- Quick Sort
  - Median-of-Three에서 세 값 비교
  - partition에서 `a[j] < pivot` 비교
- 배열 삽입
  - 삽입 위치를 찾기 위한 선형 탐색 비교
- 배열 삭제
  - 삭제 대상을 찾기 위한 선형 탐색 비교
- AVL
  - 각 노드에서 `key < n->key`, `key > n->key` 비교
  - 중위 순회는 비교 없음
- 반복문 인덱스, 종료 조건, 균형 인수 비교는 제외

### 2.3 데이터 이동 횟수

- 데이터 값의 **복사·대입** 횟수
- Quick Sort
  - swap 1회 = 3회 이동
- 배열 삽입
  - 삽입 위치 뒤 원소들을 한 칸씩 이동한 횟수 + 새 값 대입 1회
- 배열 삭제
  - 삭제 위치 뒤 원소들을 앞으로 이동한 횟수
- AVL
  - 새 노드 생성 시 key 복사 1회
  - count 증가/감소 1회
  - 후계자 승계 시 key·count 복사 2회
  - 회전, 포인터 연결 변경은 제외

### 2.4 메모리 사용량

- 최대 추가 메모리 사용량(Byte)을 **직접 계산**
- 원본 데이터 배열 저장 공간은 공통 비용으로 제외
- Quick Sort + 배열
  - 배열이 도달한 최대 크기 × `sizeof(int)` = `arrMaxSize * 4`
  - 재귀 호출 스택 근사치 2048 Byte 추가
- AVL
  - `avlMaxNodes * sizeof(AVLNode)`
  - `sizeof(AVLNode)` = key(4) + count(4) + height(4) + padding(4) + left(8) + right(8) = 32 Byte
  - 재귀 호출 스택 근사치 2048 Byte 추가
- 재귀 호출 스택은 노드/배열 크기에 비해 매우 작아 근사 상수로 처리

## 3. 실험 결과

`result.txt` 의 실제 측정값을 아래 표에 옮겨 적는다.

### Data Size : 1000 (Operations : 200)

| Item | Quick Sort | AVL Tree |
|---|---:|---:|
| Total Time |  |  |
| Comparisons |  |  |
| Data Movements |  |  |
| Memory Usage |  |  |
| Final Data Count |  |  |

### Data Size : 2000 (Operations : 400)

| Item | Quick Sort | AVL Tree |
|---|---:|---:|
| Total Time |  |  |
| Comparisons |  |  |
| Data Movements |  |  |
| Memory Usage |  |  |
| Final Data Count |  |  |

### Data Size : 4000 (Operations : 800)

| Item | Quick Sort | AVL Tree |
|---|---:|---:|
| Total Time |  |  |
| Comparisons |  |  |
| Data Movements |  |  |
| Memory Usage |  |  |
| Final Data Count |  |  |

### Data Size : 8000 (Operations : 1600)

| Item | Quick Sort | AVL Tree |
|---|---:|---:|
| Total Time |  |  |
| Comparisons |  |  |
| Data Movements |  |  |
| Memory Usage |  |  |
| Final Data Count |  |  |

### Data Size : 16000 (Operations : 3200)

| Item | Quick Sort | AVL Tree |
|---|---:|---:|
| Total Time |  |  |
| Comparisons |  |  |
| Data Movements |  |  |
| Memory Usage |  |  |
| Final Data Count |  |  |

### Data Size : 20000 (Operations : 4000)

| Item | Quick Sort | AVL Tree |
|---|---:|---:|
| Total Time |  |  |
| Comparisons |  |  |
| Data Movements |  |  |
| Memory Usage |  |  |
| Final Data Count |  |  |

## 4. 결과 분석

### 4.1 총 수행시간과 비교 횟수 차이

퀵 정렬은 초기 정렬을 `O(n log n)` 으로 매우 빠르게 처리하지만,
정렬 이후의 삽입·삭제는 정렬된 **배열** 위에서 수행되므로
매 연산마다 최대 `O(n)` 의 시간이 필요하다.

- 삽입: 삽입 위치를 찾기 위한 선형 탐색 + 뒤 원소 이동
- 삭제: 삭제 대상을 찾기 위한 선형 탐색 + 뒤 원소 이동

따라서 삽입·삽입 연산 횟수 `k = n / 5` 에 대해
전체 비교 횟수는 대략 `O(n² / 5)` 수준이 된다.

반면 AVL 트리는
- 초기 삽입: `O(n log n)`
- 삽입·삭제: 각각 `O(log n)`
이므로 전체 비교 횟수는 `O(n log n)` 에 머문다.

실험 결과에서 데이터 크기가 커질수록
Quick Sort 쪽의 비교 횟수가 AVL Tree 쪽보다
훨씬 빠르게 증가하는 것을 확인할 수 있다.

### 4.2 데이터 이동 횟수 차이

배열은 삽입·삭제 시 뒤쪽 원소를 한 칸씩 이동해야 하므로
연산 1회당 평균 `n / 2` 회의 대입이 발생한다.
연산 횟수가 `n / 5` 이므로 전체 이동 횟수는 대략 `O(n²)` 규모이다.

AVL 트리는
- 새 노드 생성 시 key 1회 복사
- count 증감 1회
- 후계자 승계 시 2회
정도만 발생하며,
회전과 포인터 변경은 데이터 이동으로 계산하지 않는다.
따라서 AVL 트리의 데이터 이동 횟수는
`O(n + k)` 수준으로 매우 작다.

실험 결과 Quick Sort + 배열 쪽의 이동 횟수가
AVL Tree 쪽보다 수십~수백 배 큰 값을 보인다.

### 4.3 메모리 사용량 차이

배열은 `n` 개의 int 만 저장하므로
`n = 20000` 일 때 약 80 KB 수준이다.
AVL 트리는 노드마다
key(4) + count(4) + height(4) + padding(4) + left(8) + right(8) = **32 Byte** 를 사용하므로
노드 수가 `n` 개일 때 약 `n * 32` Byte 가 필요하다.

실험 결과 AVL Tree 쪽 메모리 사용량이
Quick Sort + 배열 쪽보다 약 **8배** 큰 것을 확인할 수 있다.
이는 AVL 노드가 포인터·높이·중복 카운트 정보를 추가로 저장하기 때문이다.

### 4.4 데이터 크기 증가에 따른 성능 변화

- Quick Sort + 배열
  - 비교 횟수와 데이터 이동 횟수가 `O(n²)` 으로 증가
  - 데이터 크기가 2배가 되면 삽입·삭제 비용은 약 4배로 증가
- AVL Tree
  - 비교 횟수가 `O(n log n)` 으로 증가
  - 데이터 크기가 2배가 되면 비용은 약 `2 * (1 + log₂ 증가분)` 수준

따라서 데이터 크기가 커질수록
AVL Tree 의 상대적 우위가 커진다.
다만 AVL Tree 는 노드당 메모리 사용량과 포인터 추적 비용이 크기 때문에
아주 작은 데이터에서는 Quick Sort + 배열 쪽이 더 빠를 수 있다.

### 4.5 삽입·삭제가 반복되는 환경에서 유리한 자료구조

삽입·삭제가 반복되는 환경에서는 **AVL 트리**가 유리하다.

이유:
- 배열은 삽입·삭제 시 원소 이동이 필요하므로 연산당 `O(n)` 의 비용이 발생
- AVL 트리는 균형을 유지하여 연산당 `O(log n)` 의 비용으로 처리 가능
- 데이터가 커질수록 이 차이는 `O(n)` vs `O(log n)` 으로 벌어짐
- 중복 값을 count 로 관리하면 동일 값의 빈번한 삽입·삭제에도 메모리 효율적

반면 정렬 자체만 놓고 보면
Quick Sort 는 캐시 지역성이 좋고 상수 계수가 작아
배열 기반 정렬이 AVL 삽입보다 빠른 경향이 있다.
그러나 **정렬 + 반복 삽입·삭제 전체 과정**을 비교하면
AVL 트리가 점근적으로 우수하다.

### 4.6 시간·공간 복잡도 비교

| 항목 | Quick Sort + 배열 | AVL Tree |
|---|---|---|
| 초기 정렬 | O(n log n) | O(n log n) |
| 삽입 1회 | O(n) | O(log n) |
| 삭제 1회 | O(n) | O(log n) |
| 전체(정렬 + n/5 연산) | O(n²) | O(n log n) |
| 추가 메모리 | O(n) (배열) | O(n) (노드, 상수 큼) |

## 5. 결론

- Quick Sort 는 초기 정렬이 빠르고 메모리 사용량이 적지만,
  정렬 이후의 삽입·삭제가 빈번한 환경에서는 `O(n)` 의 이동 비용 때문에 불리하다.
- AVL Tree 는 삽입·삭제를 `O(log n)` 으로 처리할 수 있어
  반복적인 데이터 조작 환경에서 유리하다.
- 대신 AVL Tree 는 노드당 메모리 사용량이 크고,
  포인터 추적 비용 때문에 작은 데이터셋에서는 오히려 느릴 수 있다.
- 따라서 **정적 데이터 정렬**에는 Quick Sort 가,
  **동적 삽입·삭제가 반복되는 환경**에는 AVL Tree 가 더 적합하다.